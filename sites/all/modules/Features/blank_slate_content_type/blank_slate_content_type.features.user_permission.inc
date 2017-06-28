<?php
/**
 * @file
 * blank_slate_content_type.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function blank_slate_content_type_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create blank_slate_page content'.
  $permissions['create blank_slate_page content'] = array(
    'name' => 'create blank_slate_page content',
    'roles' => array(
      'Product' => 'Product',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any blank_slate_page content'.
  $permissions['delete any blank_slate_page content'] = array(
    'name' => 'delete any blank_slate_page content',
    'roles' => array(
      'Product' => 'Product',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own blank_slate_page content'.
  $permissions['delete own blank_slate_page content'] = array(
    'name' => 'delete own blank_slate_page content',
    'roles' => array(
      'Product' => 'Product',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any blank_slate_page content'.
  $permissions['edit any blank_slate_page content'] = array(
    'name' => 'edit any blank_slate_page content',
    'roles' => array(
      'Product' => 'Product',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blank_slate_page content'.
  $permissions['edit own blank_slate_page content'] = array(
    'name' => 'edit own blank_slate_page content',
    'roles' => array(
      'Product' => 'Product',
    ),
    'module' => 'node',
  );

  return $permissions;
}
