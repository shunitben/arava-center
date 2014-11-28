<?php
/**
 * @file
 * arava_registration_wizard.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function arava_registration_wizard_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function arava_registration_wizard_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function arava_registration_wizard_node_info() {
  $items = array(
    'accomodation' => array(
      'name' => t('Accomodation'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
    'class_room' => array(
      'name' => t('Class Room'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
    'course' => array(
      'name' => t('קורס'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
    'my_semester' => array(
      'name' => t('My Semester'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
    'one_time' => array(
      'name' => t('One Time Event'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'semester' => array(
      'name' => t('סמסטר'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
    'teacher' => array(
      'name' => t('Teacher'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('כותרת'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
