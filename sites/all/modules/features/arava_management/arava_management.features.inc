<?php
/**
 * @file
 * arava_management.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function arava_management_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "data" && $api == "data_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function arava_management_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
