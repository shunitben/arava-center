<?php

class Orders {

	protected $user;

	public function __construct() {
		global $user;
		$this->user = $user;
	}

	/**
	 * @param $type - course, accomodation
	 * @param $semester - nid. Null for all semesters.
	 * @param $uid - uid. Null for current user.
	 */
	public function getAllOrdersForUser($type, $semester = null, $uid = null) {
		if ($uid === null) {
			$uid = $this->user->uid;
		}

		$query = db_query("SELECT node.nid AS nid
												FROM node node
												INNER JOIN order_items items ON node.nid = items.entity_id
												INNER JOIN field_data_field_semester semester ON node.nid = semester.entity_id
												WHERE field_semester_target_id = $semester
													AND items.uid = $uid
													AND items.relevant = 1
													AND node.type = '$type'");

		$result = array();
		foreach ($query as $row) {
			$result[] = $row->nid;
		}
		return $result;
	}

	/**
	 * Adds an ordered item for the current user.
	 * If the user already ordered this before and cancelled, we'll create a new order anyway.
	 * @param $item
	 */
	public function addOrderItem($item) {
		$price = $this->itemCost($item);

		if ($price) {
			$this->addToPayment($item);
		}

		db_insert('order_items')
			->fields(array(
				'uid' => $this->user->uid,
				'amount' => 1,
				'entity_id' => $item,
				'pid' => 0, // @todo: put payment id here if relevant
				'relevant' => 1,
				'date_modified' => time(),
			))
			->execute();
	}

	/**
	 * Marks an item as not relevant.
	 * @param $item
	 */
	public function cancelOrderItem($item) {

		db_update('order_items')
			->fields(array(
				'relevant' => 0,
				'date_modified' => time(),
			))
			->condition('entity_id', $item)
			->condition('uid', $this->user->uid)
			->execute();
	}

	/**
	 * Check if an item costs money.
	 * @param $item
	 * @return int
	 */
	protected function itemCost($item) {
		$node = node_load($item);
		if (!empty($node->field_price) && is_array($node->field_price)) {
			return $node->field_price[LANGUAGE_NONE][0]['value'];
		}
		return 0;
	}

	/**
	 * Return a payment id if there's already an open payment for the user,
	 * @param $item
	 * @return mixed
	 */
	protected function addToPayment($item) {
		// @todo: make sure this wasn't already paid for...

		$user = user_load($this->user->uid);
		if (!empty($user->payment_in_progress) && is_array($user->payment_in_progress)) {
			return $user->payment_in_progress[LANGUAGE_NONE][0]['value'];
		}
	}

}