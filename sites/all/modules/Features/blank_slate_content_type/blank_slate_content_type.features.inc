<?php
/**
 * @file
 * blank_slate_content_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function blank_slate_content_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function blank_slate_content_type_node_info() {
  $items = array(
    'blank_slate_page' => array(
      'name' => t('Blank Slate Page'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Blank Slate Page Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
