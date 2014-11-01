<?php
/**
 * @file
 * arava_animals.features.inc
 */

/**
 * Implements hook_views_api().
 */
function arava_animals_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function arava_animals_node_info() {
  $items = array(
    'animal' => array(
      'name' => t('Animal'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
