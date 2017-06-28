<?php
/**
 * @file
 * blank_slate_content_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function blank_slate_content_type_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|blank_slate_page|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blank_slate_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|blank_slate_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_institution_settings|node|blank_slate_page|form';
  $field_group->group_name = 'group_institution_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blank_slate_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Institution Settings',
    'weight' => '1',
    'children' => array(
      0 => 'field_featured_program_id',
      1 => 'field_institution_from_is',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-institution-settings field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_institution_settings|node|blank_slate_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_page_settings|node|blank_slate_page|form';
  $field_group->group_name = 'group_page_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blank_slate_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Page Settings',
    'weight' => '2',
    'children' => array(
      0 => 'field_campaign_track_id',
      1 => 'field_category_tr',
      2 => 'field_page_form',
      3 => 'field_subject_tr',
      4 => 'field_use_site_footer',
      5 => 'field_use_site_header',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-page-settings field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_page_settings|node|blank_slate_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tracking|node|blank_slate_page|form';
  $field_group->group_name = 'group_tracking';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'blank_slate_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tracking',
    'weight' => '3',
    'children' => array(
      0 => 'field_school_tracking_code',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-tracking field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_tracking|node|blank_slate_page|form'] = $field_group;

  return $export;
}
