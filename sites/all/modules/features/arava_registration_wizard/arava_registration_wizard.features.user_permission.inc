<?php
/**
 * @file
 * arava_registration_wizard.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function arava_registration_wizard_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'signup to courses and accommodation'.
  $permissions['signup to courses and accommodation'] = array(
    'name' => 'signup to courses and accommodation',
    'roles' => array(
      'Site Manager' => 'Site Manager',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'arava_registration',
  );

  return $permissions;
}
