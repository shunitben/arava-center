<?php

class MySemesterAPI {

	/**
	 * @var
	 */
	protected $user;

	/**
	 * @var
	 */
	protected $semester_id;

	/**
	 * @var
	 */
	protected $user_semester;


	/**
	 * Construct:
	 * Load current user's my_semester node
	 */
	public function __construct($uid = null, stdClass $my_semester = null) {
    if ($uid === null) {
      global $user;
    }
		else {
      $user = user_load($uid);
    }
		$this->user = $user;
		$this->getCurrentSemester();
    if ($my_semester != null) {
      $this->user_semester = entity_metadata_wrapper('node', $my_semester);
    }
    else {
      $this->getUserSemester($this->semester_id);
    }
	}

	/**
	 * Get the id of the current semester and keep it in semester_id
	 *
	 * @return mixed
	 */
	protected function getCurrentSemester() {
		$query = db_query(" SELECT open_reg.entity_id AS entity_id
											FROM field_data_field_open_for_registration open_reg
											INNER JOIN field_data_field_semester_dates dates ON open_reg.entity_id = dates.entity_id
											WHERE field_open_for_registration_value = 1
											ORDER BY dates.field_semester_dates_value ASC");
		foreach ($query as $row) {
			$result = $row->entity_id; // override to get the latest open semester, just in case.
		}
		$this->semester_id = $result;
	}

	/**
	 * Get the user's my_semester node and keep it in user_semester
	 *
	 * @param $semester_id
	 * @return bool|mixed|null
	 */
	protected function getUserSemester($semester_id) {
		$query = db_query(" SELECT user.entity_id
 											FROM field_data_field_user user
 											INNER JOIN field_data_field_semester semester
											WHERE field_user_target_id = " . $this->user->uid . "
											AND field_semester_target_id = " . $semester_id);
		foreach ($query as $row) {
			$node = node_load($row->entity_id);
			$this->user_semester = entity_metadata_wrapper('node', $node);
			return;
		}
		// if user hasn't a my_semester node yet, create one:
		$this->createMySemester();
	}

	/**
	 * Create a my_semester node for a user
	 */
	protected function createMySemester() {
		$values = array(
			'type' => 'my_semester',
			'uid' => $this->user->uid,
			'status' => 1,
			'comment' => 0,
			'promote' => 0,
		);
		$entity = entity_create('node', $values);
		$ewrapper = entity_metadata_wrapper('node', $entity);
		$semester = node_load($this->semester_id);
		$ewrapper->title->set($this->user->name . ' - ' . $semester->title);
		$ewrapper->field_user->set(intval($this->user->uid));
		$ewrapper->field_semester->set(intval($this->semester_id));
		$ewrapper->save();

		$this->user_semester = $ewrapper;
	}

  public function coursesCollision($course_ids) {
    $times = array();
    $collisions = array();
    $courses = node_load_multiple($course_ids);
    foreach ($courses as $course) {
      foreach ($course->field_lesson_times[LANGUAGE_NONE] as $lesson_time) {
        // check collision
        foreach ($times as $time) {
          if (($lesson_time['value'] >= $time['start'] && $lesson_time['value'] < $time['end'])
          || ($lesson_time['value2'] > $time['start'] && $lesson_time['value2'] <= $time['end'])) {
            $collisions[$time['course']] = $time['course_name'];
            $collisions[$course->nid] = $course->title;
          }
        }
        // add to found times
        $times[] = array(
          'course' => $course->nid,
          'course_name' => $course->title,
          'start' => $lesson_time['value'],
          'end' => $lesson_time['value2'],
        );
      }
    }

    return !empty($collisions) ? $collisions : false;
  }

	/**
	 * Get all courses ids for the user
	 *
	 * @return array
	 */
	public function getAllCoursesForUser() {
		if ($this->user_semester == null) return array();

		$courses = array();
		foreach ($this->user_semester->field_my_courses as $course) {
			$courses[] = $course->field_course->getIdentifier();
		}
		return $courses;
	}

	/**
	 * Add a course to the user's my_semester
	 *
	 * @param $course
	 */
	public function addCourse($course) {
		$user_semester_node = node_load($this->user_semester->getIdentifier());

		$course_field_collection = entity_create('field_collection_item', array('field_name' => 'field_my_courses'));
		$course_field_collection->setHostEntity('node', $user_semester_node);
		$course_field_collection_wrapper = entity_metadata_wrapper('field_collection_item', $course_field_collection);
		$course_field_collection_wrapper->field_course->set($course);
		$course_field_collection_wrapper->save(true);

	  field_attach_update('node', $user_semester_node);

    $this->updatePaymentDueTotal($user_semester_node);
	}


	/**
	 * Remove a course from the user's my semester
	 *
	 * @param $course
	 */
	public function removeCourse($course) {

		$user_semester_node = node_load($this->user_semester->getIdentifier());

		foreach ($user_semester_node->field_my_courses[LANGUAGE_NONE] as $key => $value) {
			$delete_me_id = $value['value'];
			$field_collection = entity_load('field_collection_item', array($delete_me_id));
			$field_collection = array_pop($field_collection);
			$field_collection_course = $field_collection->field_course[LANGUAGE_NONE][0]['target_id'];
			if ($field_collection_course == $course) {
				entity_delete_multiple('field_collection_item', array($delete_me_id));
				unset($user_semester_node->field_my_courses[LANGUAGE_NONE][$key]);
				$user_semester_node->field_my_courses[LANGUAGE_NONE] = array_values($user_semester_node->field_my_courses[LANGUAGE_NONE]);
				field_attach_update('node', $user_semester_node);
				break;
			}
		}

    $this->updatePaymentDueTotal($user_semester_node);
	}

  /**
   * Get the selected accomodation nid, if exists
   * @return int / null
   */
  public function getAccomodationForUser() {
    if ($this->user_semester == null) return null;

    $accomodation = $this->user_semester->field_my_accomodation->value();

    return !empty($accomodation) ? $accomodation->nid : null;
  }

  /**
   * Set the user's selected accomodation to my_semester
   * @param $accomodation
   */
  public function selectAccomodation($accomodation) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());

    $user_semester_node->field_my_accomodation[LANGUAGE_NONE][0]['target_id'] = $accomodation;
    field_attach_update('node', $user_semester_node);

    $this->updatePaymentDueTotal($user_semester_node);
  }

  /**
   * Get all the presence info for a user
   * @return array
   */
  public function getPresenceInfoForUser() {
    if ($this->user_semester == null) return null;
    return $this->user_semester->field_days_present->value();
  }

  public function setPresenceInfo($presence_days) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());

    $days = array();
    foreach ($presence_days as $day) {
      if (!empty($day)) {
        $days[]['value'] = $day;
      }
    }
    $user_semester_node->field_days_present[LANGUAGE_NONE] = $days;

    field_attach_update('node', $user_semester_node);

    $this->updatePaymentDueTotal($user_semester_node);
  }

  /**
   * Get all the meals info for a user
   * @return array
   */
  public function getMealsInfoForUser() {
    // some of the info (allergies and preferences) lives in the user
    // and some (days of presence, extra guests) lives in my_semester
    $user = user_load($this->user->uid);
    $user_wrapper = entity_metadata_wrapper('user', $user);
    $meals_info = array(
      'gluten' => $user_wrapper->field_gluten->value(),
      'dairy' => $user_wrapper->field_dairy->value(),
      'peanuts' => $user_wrapper->field_peanuts->value(),
      'other_allergies' => $user_wrapper->field_other_allergies->value(),
      'vegan' => $user_wrapper->field_vegan->value(),
    );
    if ($this->user_semester != null) {
      $meals_info['days_present'] = $this->user_semester->field_days_present->value();
      $meals_info['extra_guests'] = $this->user_semester->field_extra_guests_num->value();
      $meals_info['extra_days_present'] = $this->user_semester->field_extra_days_present->value();
    }


    return $meals_info;
  }

  public function setMealsFoodInfo($allergies, $other_allergies, $vegan) {
    $user = user_load($this->user->uid);
    $user->field_gluten[LANGUAGE_NONE][0]['value'] = $allergies['gluten'];
    $user->field_dairy[LANGUAGE_NONE][0]['value'] = $allergies['dairy'];
    $user->field_peanuts[LANGUAGE_NONE][0]['value'] = $allergies['peanuts'];
    $user->field_other_allergies[LANGUAGE_NONE][0]['value'] = $other_allergies;
    $user->field_vegan[LANGUAGE_NONE][0]['value'] = $vegan;

    field_attach_update('user', $user);
  }

  public function setMealsPresenceInfo($num_guests, $guests_presence_days) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());

    $user_semester_node->field_extra_guests_num[LANGUAGE_NONE][0]['value'] = !empty($num_guests) ? $num_guests : 0;

    $days = array();
    foreach ($guests_presence_days as $day) {
      if (!empty($day)) {
        $days[]['value'] = $day;
      }
    }
    $user_semester_node->field_extra_days_present[LANGUAGE_NONE] = $days;

    field_attach_update('node', $user_semester_node);

    $this->updatePaymentDueTotal($user_semester_node);
  }

  /**
   * Get all the extra info for a user
   * @return array
   */
  public function getExtraInfoForUser() {
    if ($this->user_semester == null) return null;

    $extra_info = array(
      'comments' => $this->user_semester->field_comments->value(),
      'takanon_moa' => $this->user_semester->field_takanon_moa->value(),
      'takanon_school' => $this->user_semester->field_takanon_school->value(),
      'takanon_amuta' => $this->user_semester->field_takanon_amuta->value(),
      'health_declaration' => $this->user_semester->field_health_declaration->value(),
      'waver' => $this->user_semester->field_waver->value(),
    );

    return $extra_info;
  }

  /**
   * Make sure all takanons were signed
   * @return bool
   */
  public function validateExtraInfoForUser() {
    $extra_info = $this->getExtraInfoForUser();
    unset($extra_info['comments']);
    foreach ($extra_info as $info) {
      if (!$info) {
        return false;
      }
    }
    return true;
  }



//  /**
//   * Set the user's extra info to my_semester
//   * @param $extra_info
//   */
//  public function setExtraInfo($extra_info) {
//    $user_semester_node = node_load($this->user_semester->getIdentifier());
//
//    $user_semester_node->field_comments[LANGUAGE_NONE][0]['value'] = $extra_info['comments'];
//    $user_semester_node->field_takanon_moa[LANGUAGE_NONE][0]['value'] = $extra_info['takanon_moa'];
//    $user_semester_node->field_takanon_school[LANGUAGE_NONE][0]['value'] = $extra_info['takanon_school'];
//    $user_semester_node->field_takanon_amuta[LANGUAGE_NONE][0]['value'] = $extra_info['takanon_amuta'];
//    $user_semester_node->field_health_declaration[LANGUAGE_NONE][0]['value'] = $extra_info['health_declaration'];
//    $user_semester_node->field_waver[LANGUAGE_NONE][0]['value'] = $extra_info['waver'];
//
//    field_attach_update('node', $user_semester_node);
//  }

  /**
   * Set the user's extra info to my_semester
   * @param $extra_info
   */
  public function setComment($comment) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());

    $user_semester_node->field_comments[LANGUAGE_NONE][0]['value'] = $comment;

    field_attach_update('node', $user_semester_node);
  }

  /**
   * Save that the user has agreed to a takanon
   * @param $field
   */
  public function setAgreement($field) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());

    $user_semester_node->$field = array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => '1'
        )
      )
    );

    field_attach_update('node', $user_semester_node);
  }

  /**
   * Update Payment Total - should be called after any update to my semester that might affect the payment
   *
   * @param $user_semester // we need this fresh, with any new info, not cached
   * @return int
   */
  public function updatePaymentDueTotal($user_semester) {
    $user_semester_wrapper = entity_metadata_wrapper('node', $user_semester);

    // Payment total includes accommodation, courses, and extra meals.
    // @todo: meals calculation, when we know the requirements.

    $price = 0;

    $accomodation = $user_semester_wrapper->field_my_accomodation->value();
    if (!empty($accomodation)) {
      $price += $user_semester_wrapper->field_my_accomodation->field_price->value();
    }

    $my_courses = !empty($user_semester->field_my_courses) ? $user_semester->field_my_courses[LANGUAGE_NONE] : array();
    foreach ($my_courses as $my_course) {
      // depending on the situation, my_courses may be full field collection objects, or just a reference
      if (!isset($my_course['field_course'])) {
        if (isset($my_course['value'])) {
          $my_course = entity_load('field_collection_item', array($my_course['value']));
        }
        $my_course = array_shift($my_course);
        $target_id = $my_course->field_course[LANGUAGE_NONE][0]['target_id'];
      }
      else {
        $target_id = $my_course['field_course'][LANGUAGE_NONE][0]['target_id'];
      }
      if (!empty($target_id)) {
        $node = node_load($target_id);
        if ($node != null) {
          $course = entity_metadata_wrapper('node', $node);
          $course_price = $course->field_price->value();
          if ($course_price > 0) {
            $price += $course_price;
          }
        }
      }
    }

    // no need to save if nothing's changed
    if ($price != $user_semester_wrapper->field_payment_total->value()) {
      $user_semester_node = node_load($this->user_semester->getIdentifier());
      $user_semester_node->field_payment_total[LANGUAGE_NONE][0]['value'] = $price;
      field_attach_update('node', $user_semester_node);
    }

    return $price;
  }

  public function getPaymentDue() {

    $due = $this->user_semester->field_payment_total->value();

    $accommodation = $this->user_semester->field_my_accomodation->value();
    if (!empty($accommodation)) {

      // For now, we don't pay for the room when first ordering, only after approval.
      // We only pay for the no-accommodation plan (or in other words, don't pay the for the bed right now), unless the
      // semester was approved for paying accommodation.

      // so - is the "pay for accommodation on registration" flag off?
      $pay_for_bed_later = !variable_get('arava_center_pay_for_accomodation_on_registration');

      // and is the semester open for paying accommodation?
      $semester = node_load($this->semester_id);
      $semester = entity_metadata_wrapper('node', $semester);
      $semester_pay_for_beds_approved = $semester->field_approved_pay_accomodation->value();

      if ($pay_for_bed_later && !$semester_pay_for_beds_approved) {
        $query = db_select('field_data_field_price', 'price');
        $query->join('node', 'node', 'price.entity_id = node.nid');
        $query->condition('node.type', 'accomodation');
        $query->addExpression('MIN(field_price_value)', 'min_field_price_value');

        $lowest_accomodation = $query->execute()->fetchField();
        $my_accomodation = $this->user_semester->field_my_accomodation->field_price->value();
        $diff = $my_accomodation - $lowest_accomodation;
        $due = $due - $diff;
      }

    }

    $paid = $this->user_semester->field_payment_made->value();

    return $due - $paid;
  }

//  public function getRemainingPayment() {
//
//    $due = $this->user_semester->field_payment_total->value();
//    $paid = $this->user_semester->field_payment_made->value();
//
//    return $due - $paid;
//  }

  public function getMadePayment() {
    return $this->user_semester->field_payment_made->value();
  }

  /**
   * After the user had made a payment and we saved the confirmation code from tranzilla,
   * we add the amount they paid to the my_semester
   * @param $amount
   */
  public function addPayment($amount) {
    $user_semester_node = node_load($this->user_semester->getIdentifier());
    $user_semester_node->field_payment_made[LANGUAGE_NONE][0]['value'] += $amount;
    field_attach_update('node', $user_semester_node);
  }

  public function getSemesterId() {
    return $this->semester_id;
  }
  
  public function getMySemesterId() {
    return $this->user_semester->getIdentifier();
  }
  
  public function getUser() {
    return user_load($this->user->uid);
  }
}