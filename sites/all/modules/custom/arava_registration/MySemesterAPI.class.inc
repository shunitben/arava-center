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
	public function __construct() {
		global $user;
		$this->user = $user;
		$this->getCurrentSemester();
		$this->getUserSemester($this->semester_id);
	}

	/**
	 * @return mixed
	 */
	protected function getCurrentSemester() {
		$query = db_query(" SELECT open.entity_id AS entity_id
											FROM field_data_field_open_for_registration open
											WHERE field_open_for_registration_value = 1");
		foreach ($query as $row) {
			$result = $row->entity_id; // override to get the latest open semester, just in case.
		}
		$this->semester_id = $result;
	}

	/**
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

	/**
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

	}


	/**
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
	}

}