<?php
/**
 * @file
 * arava_registration_wizard.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function arava_registration_wizard_taxonomy_default_vocabularies() {
  return array(
    'faculties' => array(
      'name' => 'Faculties',
      'machine_name' => 'faculties',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
