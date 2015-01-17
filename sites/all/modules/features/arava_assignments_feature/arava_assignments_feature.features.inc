<?php
/**
 * @file
 * arava_assignments_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function arava_assignments_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function arava_assignments_feature_node_info() {
  $items = array(
    'assignment' => array(
      'name' => t('מטלות'),
      'base' => 'node_content',
      'description' => t('שיעורי בית, בחנים ומבחנים'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
