<?php
/**
 * @file
 * arava_teachers.features.inc
 */

/**
 * Implements hook_node_info().
 */
function arava_teachers_node_info() {
  $items = array(
    'message' => array(
      'name' => t('Message'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
