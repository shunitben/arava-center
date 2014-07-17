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

  // Exported permission: 'edit field_dairy'.
  $permissions['edit field_dairy'] = array(
    'name' => 'edit field_dairy',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_gluten'.
  $permissions['edit field_gluten'] = array(
    'name' => 'edit field_gluten',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_other_allergies'.
  $permissions['edit field_other_allergies'] = array(
    'name' => 'edit field_other_allergies',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_peanuts'.
  $permissions['edit field_peanuts'] = array(
    'name' => 'edit field_peanuts',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_vegan'.
  $permissions['edit field_vegan'] = array(
    'name' => 'edit field_vegan',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_dairy'.
  $permissions['edit own field_dairy'] = array(
    'name' => 'edit own field_dairy',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_gluten'.
  $permissions['edit own field_gluten'] = array(
    'name' => 'edit own field_gluten',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_other_allergies'.
  $permissions['edit own field_other_allergies'] = array(
    'name' => 'edit own field_other_allergies',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_peanuts'.
  $permissions['edit own field_peanuts'] = array(
    'name' => 'edit own field_peanuts',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_vegan'.
  $permissions['edit own field_vegan'] = array(
    'name' => 'edit own field_vegan',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'signup to courses and accommodation'.
  $permissions['signup to courses and accommodation'] = array(
    'name' => 'signup to courses and accommodation',
    'roles' => array(
      'Site Manager' => 'Site Manager',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'arava_registration',
  );

  // Exported permission: 'view field_dairy'.
  $permissions['view field_dairy'] = array(
    'name' => 'view field_dairy',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_gluten'.
  $permissions['view field_gluten'] = array(
    'name' => 'view field_gluten',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_other_allergies'.
  $permissions['view field_other_allergies'] = array(
    'name' => 'view field_other_allergies',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_peanuts'.
  $permissions['view field_peanuts'] = array(
    'name' => 'view field_peanuts',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_vegan'.
  $permissions['view field_vegan'] = array(
    'name' => 'view field_vegan',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_dairy'.
  $permissions['view own field_dairy'] = array(
    'name' => 'view own field_dairy',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_gluten'.
  $permissions['view own field_gluten'] = array(
    'name' => 'view own field_gluten',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_other_allergies'.
  $permissions['view own field_other_allergies'] = array(
    'name' => 'view own field_other_allergies',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_peanuts'.
  $permissions['view own field_peanuts'] = array(
    'name' => 'view own field_peanuts',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_vegan'.
  $permissions['view own field_vegan'] = array(
    'name' => 'view own field_vegan',
    'roles' => array(
      'Site Manager' => 'Site Manager',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
