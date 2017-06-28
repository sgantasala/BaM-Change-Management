<?php

#region Overview Page

/**
 * List callback which shows an overview page of all the custom Lists and their descriptions.
 */
function eddy_listing_overview_page() {

    try{

        $result = db_query("SELECT * FROM {eddy_listing} ORDER BY name", array(), array('fetch' => PDO::FETCH_ASSOC));

        $header = array(
          t('Title'),
          t('Description'),
          t('Listing Type'),
          t('Feature Type Id'),
          t('Operation'),
        );

        $rows = array();
        foreach ($result as $list) {
            $rows[] = array(
                'title' => $list['name'],
                'description' => $list['description'],
                'type' => $list['type'],
                'featured_type_id' => $list['featured_list'],
                'edit' => l(t('config List'), 'admin/structure/eddy_listing/manage/' . $list['id'] . '/edit'),
            );
        }

        return theme('table', array('header' => $header, 'rows' => $rows));

    }
    catch(Exception $e){

        if(module_exists('devel')){
            dpm($e);
        }

        return "";

    }

}


/**
 * Returns HTML for a List title, List type and description for the List overview page.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: The List's title.
 *	 - listing type: The List's type.
 *   - description: The List's description.
 *
 */
function theme_eddy_listing_admin_overview($variables) {

    $output = check_plain($variables['title']);
    $output .= '<div class="description">Listing Type: ' . filter_xss_admin($variables['type']) . '</div>';
    $output .= '<div class="description">' . filter_xss_admin($variables['description']) . '</div>';

    return $output;

}

#endregion


#region Create List

/**
 * List callback; Build the form that handles the adding of a custom list.
 */
function eddy_listing_add_list($form, &$form_state, $type, $list = array()) {

    $form = eddy_listings_form($list);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    return $form;

}


/**
 * List callback; Build the form that handles the editing of a custom list.
 */
function eddy_listing_edit_list($form, &$form_state, $type, $list) {

    $form = eddy_listings_form($list);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['update'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('eddy_listing_edit_list_update'),
    );

    // custom lists may be deleted.
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#access' => $type == 'edit',
      '#submit' => array('eddy_listing_delete_submit'),
    );

    return $form;

}


/**
 * Submit callback function for insterting a List.
 */
function eddy_listing_add_list_submit($form, &$form_state) {

    if(!empty($form_state['values']['include_types']))
        $form_state['values']['include_types'] = serialize($form_state['values']['include_types']);
	else
        $form_state['values']['include_types'] = serialize(array());

	$list = $form_state['values'];

	$path = 'admin/structure/eddy_listing/manage/';

    $fields = eddy_listings_fields($list);

    $fields['machine_name'] = $list['machine_name'];

    try
    {

		$lid = db_insert('eddy_listing')
		->fields($fields)
		->execute();

        drupal_set_message(t('Your configuration has been saved.'));

        module_invoke_all('eddy_listing_insert', $form, $form_state, $lid);

		cache_clear_all();

	}
	catch (Exception $e)
	{

		drupal_set_message(t('There was an issue with your configuration. Try to run update.php to resolve the issue. If issue is still there after you run update, please contact administrator.'));

        if(module_exists('devel')){
            dpm($e);
        }

	}

	$form_state['redirect'] = $path . $list['listing_name'];

}

#endregion


#region Update List

/**
 * Submit callback function for updating a List.
 */
function eddy_listing_edit_list_update($form, &$form_state) {

    $list = $form_state['values'];
    $lid = $form['#list']['id'];

	$fields  = eddy_listings_fields($list);

	try {

		db_update('eddy_listing')
		    ->fields($fields)
		    ->condition('id', $lid)
		    ->execute();

        drupal_set_message(t('Your configuration has been saved.'));

        module_invoke_all('eddy_listing_update', $form, $form_state, $lid);

	}
	catch (Exception $e) {

        drupal_set_message(t('There was an error updating this list. Try to run update.php to resolve the issue. If issue is still there after you run update, please contact administrator.'), 'error');

        if(module_exists('devel')){
            dpm($e);
        }

	}

}

#endregion


#region Delete List

/**
 * Submit function for the 'Delete' button on the listing editing form.
 */
function eddy_listing_delete_submit($form, &$form_state) {
	$form_state['redirect'] = 'admin/structure/eddy_listing/manage/'.$form_state['build_info']['args'][1]['id'].'/delete';
}


/**
 * Listing callback; Get a confirm form for deletion of a custom listing.
 */
function eddy_listing_delete_list_page($list) {
	return drupal_get_form('eddy_listing_delete_list_confirm', $list);
}


/**
 * Build a confirm form for deletion of a custom listing.
 */
function eddy_listing_delete_list_confirm($form, &$form_state, $list) {
	$form['#list'] = $list;
	$caption = '<p>' . t('This action cannot be undone.') . '</p>';
	return confirm_form($form, t('Are you sure you want to delete this listing: %name?', array('%name' => $list['name'])), 'admin/structure/eddy_listing/manage/' . $list['id'], $caption, t('Delete'));
}


/**
 * Submit callback function for deleting a List.
 */
function eddy_listing_delete_list_confirm_submit($form, &$form_state) {

    $list = $form['#list'];
	$form_state['redirect'] = 'admin/structure/eddy_listing';

    try{

        // Delete the List.
        db_delete('eddy_listing')
          ->condition('id', $list['id'])
          ->execute();

        db_delete('block')
          ->condition('delta', $list['id'])
          ->execute();

        db_delete('block_node_type')
         ->condition('module', 'eddy_listing')
          ->condition('delta', $list['id'])
          ->execute();

        cache_clear_all();

        module_invoke_all('eddy_listing_delete', $list);

    }
    catch(Exception $e){

        if(module_exists('devel')){
            dpm($e);
        }

    }

}

#endregion


#region Misc Helper Function

/**
 * Builds the form array for both Instert and Update forms.
 */
function eddy_listings_form($list){

    $base_content_url = get_base_content_url();
    $form['#list'] = $list;

    $form['listing_name'] = array(
      '#type' => 'textfield',
      '#title' => t("Listing Name"),
      '#required' => TRUE,
      '#default_value' => empty($list['name']) ? '' : $list['name'],
    );

    if(count($list) == 0){
        $form['machine_name'] = array(
          '#type' => 'machine_name',
          '#title' => t('Machine Name'),
          '#default_value' => '',
          '#maxlength' => 64,
          '#description' => t('A unique name for a Listing.'),
          '#machine_name' => array(
            'exists' => 'listing_edit_machine_name_exists',
            'source' => array('listing_name'),
            'label' => t('Machine Name'),
            'replace_pattern' => '[^a-z0-9-]+',
            'replace' => '-',
          ),
        );
    }

    $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => empty($list['description']) ? '' : $list['description'],
    );

    $form['listing_attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t("Basic Settings"),
      '#description' => t('Please select the attributes desired for the listing.'),
      '#collapsible' => FALSE,
    );

    $form['listing_attributes']['listing_type'] = array(
      '#type' => 'select',
      '#title' => t("Type of listing:"),
      '#options' => array(
          'school' => t('Institutions'),
          'campus' => t('Campuses'),
          'program' => t('Programs'),
      ),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#default_value' => empty($list['type']) ? array() : $list['type'],
      '#required' => TRUE,
    );

    $form['listing_attributes']['featured'] = array(
      '#type' => 'checkbox',
      '#title' => t('Featured Listing'),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#default_value' => empty($list['featured']) ? 0 : $list['featured'],
    );

    $form['listing_attributes']['featured_options_schools'] = array(
      '#type' => 'select',
      '#title' => t("Featured List:"),
      '#options' => eddy_listing_get_featured_list(1),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('value' => 'school'),
          ':input[name="featured"]' => array('checked' => TRUE),
          ),
      ),
      '#default_value' => empty($list['featured_list']) ? array() : $list['featured_list'],
    );

    $campus_options = eddy_listing_get_featured_list(2);
    if(!empty($campus_options )) {
        $form['listing_attributes']['featured_options_campus'] = array(
          '#type' => 'select',
          '#title' => t("Featured List:"),
          '#options' => $campus_options,
          '#prefix' => '<div class="list-form-item inline">',
          '#suffix' => '</div>',
          '#states' => array(
              'visible' => array(
              ':input[name="listing_type"]' => array('value' => 'campus'),
              ':input[name="featured"]' => array('checked' => TRUE),
              ),
          ),
          '#default_value' => empty($list['featured_list']) ? array() : $list['featured_list'],
        );
    }
    $form['listing_attributes']['featured_options_programs'] = array(
      '#type' => 'select',
      '#title' => t("Featured List:"),
      '#options' => eddy_listing_get_featured_list(3),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('value' => 'program'),
          ':input[name="featured"]' => array('checked' => TRUE),
          ),
      ),
      '#default_value' => empty($list['featured_list']) ? array() : $list['featured_list'],
    );

    $recordCountOptions = array();
    foreach (range(1, 100) as $val) {
        $recordCountOptions[$val] = t("$val");
    }
    $recordCountOptions["ALL"] = t("All");

    $form['listing_attributes']['record_count'] = array(
      '#type' => 'select',
      '#title' => t("No. of records to display"),
      '#options' => $recordCountOptions,
      '#default_value' => empty($list['total_records_to_display']) ? array() : $list['total_records_to_display'],
      '#required' => TRUE,
    );

    $form['listing_attributes']['show_pager'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Pager'),
      '#description' => t('Pager can only be applied to listings that show in the main content region.'),
      '#default_value' => empty($list['show_pager']) ? 0 : $list['show_pager'],
    );

    $form['listing_attributes']['show_pager_location'] = array(
      '#type' => 'select',
      '#title' => t("Where to display pager?"),
      '#options' => array(
          'both' => t('Both'),
          'bottom' => t('Bottom of Listing'),
          'top' => t('Top of Listing'),
      ),
      '#default_value' => empty($list['show_pager_location']) ? array() : $list['show_pager_location'],
      '#states' => array(
        'visible' => array(
          ':input[name="show_pager"]' => array('checked' => TRUE),
          ),
        'required' => array(
          ':input[name="show_pager"]' => array('checked' => TRUE),
          ),
      ),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
    );

    $form['listing_attributes']['user_change_records'] = array(
      '#type' => 'checkbox',
      '#title' => t('Open to user to change records to display'),
      '#states' => array(
        'visible' => array(
          ':input[name="show_pager"]' => array('checked' => TRUE),
          ),
      ),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#description' => t('Allow user to change view records when browsing Product list page.'),
      '#default_value' => empty($list['user_change_records']) ? 0 : $list['user_change_records'],
    );

    //Added for update 7004
    //$form['listing_attributes']['random_item_from_list'] = array(
    //  '#type' => 'checkbox',
    //  '#title' => t('Show only one result randomly from the list of results.'),
    //  '#default_value' => empty($list['random_item_from_list']) ? 0 : $list['random_item_from_list'],
    //);

    $form['listing_attributes']['show_nested_programs'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show nested Programs for each item in this list.'),
      '#default_value' => empty($list['show_nested_programs']) ? 0 : $list['show_nested_programs'],
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('!value' => 'program'),
          ':input[name="attach_list"]' => array('checked' => FALSE),
        ),
      ),
    );

    $form['listing_attributes']['show_nested_campuses'] = array(
       '#type' => 'checkbox',
       '#title' => t('Show nested Campuses for each item in this list.'),
       '#default_value' => empty($list['show_nested_campuses']) ? 0 : $list['show_nested_campuses'],
       '#states' => array(
          'visible' => array(
              ':input[name="listing_type"]' => array('value' => 'school'),
          ),
       ),
    );
    //Added for update 7015
    $form['listing_attributes']['remove_capped'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove Capped Records.'),
      '#default_value' => empty($list['remove_capped']) ? 0 : $list['remove_capped'],
    );

    $form['listing_attributes']['show_non_for_profit_list'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show only Non For Profit schools.'),
      '#default_value' => empty($list['show_non_for_profit_list']) ? 0 : $list['show_non_for_profit_list'],
    );

    $form['listing_attributes']['nested_record_count'] = array(
      '#type' => 'select',
      '#title' => t("Number of nested Programs."),
      '#options' => array(
          1 => t('1'),
          2 => t('2'),
		3 => t('3'),
		4 => t('4'),
		5 => t('5'),
		10 => t('10'),
		15 => t('15'),
		25 => t('25'),
		50 => t('50'),
		100 => t('100'),
		999 => 'All',
	),
	'#states' => array(
      'visible' => array(
        ':input[name="show_nested_programs"]' => array('checked' => TRUE),
		),
	),
	'#default_value' => empty($list['nested_record_count']) ? array() : $list['nested_record_count'],
  );

    $form['listing_attributes']['attach_list'] = array(
      '#type' => 'checkbox',
      '#title' => t('Attach another list to each item in this list.'),
      '#default_value' => empty($list['attach_list']) ? 0 : $list['attach_list'],
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('!value' => 'program'),
          ':input[name="show_nested_programs"]' => array('checked' => FALSE),
        ),
      ),
    );

    try{

        $listIdNames = db_query("SELECT * FROM {eddy_listing} WHERE type = 'program' ORDER BY id", array(), array('fetch' => PDO::FETCH_ASSOC));

        $aggrListOptions[0] = '--Select--';
        foreach ($listIdNames as $listIdName) {
            $aggrListOptions[$listIdName['id']] = $listIdName['name'];
        }

        $form['listing_attributes']['attached_list_id'] = array(
          '#type' => 'select',
          '#title' => t("Attached List."),
          '#options' => $aggrListOptions,
          '#default_value' => empty($list['attached_list_id']) ? 0 : $list['attached_list_id'],
          '#states' => array(
            'visible' => array(
              ':input[name="attach_list"]' => array('checked' => TRUE),
            ),
          ),
        );

    }
    catch(Exception $e){

        if(module_exists('devel')){
            dpm($e);
        }

    }

    $form['filtering_sorting'] = array(
      '#type' => 'fieldset',
      '#title' => t("Filtering and Sorting"),
      '#description' => t('Filtering and sorting configuration.'),
      '#collapsible' => TRUE,
    );

    $filterSourceOptions = array();
    $filterSourceOptions['none'] = t('No Filtering');
    $filterSourceOptions['node'] = t('Content Page (Current Node)');
    $filterSourceOptions['qs'] = t('Query String Params (Usually for AJAX)');

    if(variable_get('eddy_core_application_id') == 1)
        $filterSourceOptions['url'] = t('URL');

    $form['filtering_sorting']['filter_source'] = array(
      '#type' => 'select',
      '#title' => t("How should this content be filtered."),
      '#description' => t('This is used to determine how a list will get its filters.'),
      '#options' => $filterSourceOptions,
      '#default_value' => empty($list['filter_source']) ? array() : $list['filter_source'],
    );

    $form['filtering_sorting']['sort'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use a custom sort order.'),

      '#default_value' => empty($list['sort']) ? 0 : $list['sort'],
    );

    $form['filtering_sorting']['sort_program_by'] = array(
      '#type' => 'select',
      '#title' => t("Sort By"),
      '#description' => t('How you would like the listing to be sorted by.'),
      '#options' => array(
          'alphabetical' => t('Alphabetical'),
          'types' => t('Program Type'),
          'levels' => t('Degree Level'),
          'subjects' => t('Subject'),
          'categories' => t('Category'),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="sort"]' => array('checked' => TRUE),
          ':input[name="listing_type"]' => array('value' => 'program'),
        ),
      ),
      '#default_value' => empty($list['sort_by']) ? array() : $list['sort_by'],
    );

    $form['filtering_sorting']['sort_school_by'] = array(
      '#type' => 'select',
      '#title' => t("Sort By"),
      '#description' => t('How you would like the listing to be sorted by.'),
      '#options' => array(
          'alphabetical' => t('Alphabetical'),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="sort"]' => array('checked' => TRUE),
          ':input[name="listing_type"]' => array('!value' => 'program'),
        ),
      ),
      '#default_value' => empty($list['sort_by']) ? array() : $list['sort_by'],
    );

    $form['filtering_sorting']['group_by'] = array(
      '#type' => 'checkbox',
      '#title' => t("Group By"),
      '#description' => t('Would you would like the sorted list to be grouped by your sorted value.'),
      '#states' => array(
        'visible' => array(
          ':input[name="sort"]' => array('checked' => TRUE),
          ':input[name="sort_program_by"]' => array('!value' => 'alphabetical'),
          ),
      ),
      '#default_value' => empty($list['group_by']) ? 0 : $list['group_by'],
    );

    $form['include_exclude_filters'] = array(
      '#type' => 'fieldset',
      '#title' => t("Include or Exclude Filters"),
      //'#description' => t('Filtering and sorting configuration.'),
      '#collapsible' => TRUE,
    );

    $campus_types = _eddy_listing_get_campus_types();

    if(!empty($campus_types)){

        $form['include_exclude_filters']['include_types'] = array(
          '#type' => 'checkboxes',
          '#title' => t("Include Program Types"),
          '#description' => t('If page filters are needed then leave blank as this will override them.'),
          '#options' => $campus_types,
          '#default_value' => empty($list['include_types']) ? array() : unserialize($list['include_types']),
        );

    }

    $form['include_exclude_filters']['include_campus_types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Include Campus Types'),
      '#description' => t('If page filters are needed then leave blank as this will override them.'),
      '#options' => array(
          1 => 'Online',
          2 => 'Campus',
      ),
      '#default_value' => empty($list['include_campus_types']) ? array() : unserialize($list['include_campus_types']),
    );

    $form['include_exclude_filters']['online_when_empty'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Online when no results are returned.'),
      '#default_value' => empty($list['online_when_empty']) ? 0 : $list['online_when_empty'],
    );

    $form['type_school'] = array(
      '#type' => 'fieldset',
      '#title' => t("Institution Display Items"),
      '#description' => t('Please select school fields to display in listing.'),
      '#collapsible' => TRUE,
    );

    $form['type_school']['show_school_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Institution title'),
      '#default_value' => empty($list['show_school_title']) ? 0 : $list['show_school_title'],
    );

    $form['type_school']['show_school_description'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Institution description'),
      '#default_value' => empty($list['show_school_description']) ? 0 : $list['show_school_description'],
    );

    $form['type_school']['show_school_logo'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Institution logo'),
      '#default_value' => empty($list['show_school_logo']) ? 0 : $list['show_school_logo'],
    );

    $form['type_school']['logo_size'] = array(
      '#type' => 'select',
      '#title' => t("Logo Size"),
      '#description' => t('The size of the logo to display'),
      '#options' => array(
          '150x50' => t('150x50'),
          '120x40' => t('120x40'),
          '240x80' => t('240x80'),
      ),
      '#prefix' => '<div class="list-form-item inline">',
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          ':input[name="show_school_logo"]' => array('checked' => TRUE),
          ),
      ),
      '#default_value' => empty($list['logo_size']) ? array() : $list['logo_size'],
    );

    $form['type_school']['logo_150x50'] = array(
      '#type' => 'image_button',
      '#title' => t("Sampe Logo"),
      '#description' => t('The logo to display'),
      '#states' => array(
        'visible' => array(
          ':input[name="show_school_logo"]' => array('checked' => TRUE),
          ':input[name="logo_size"]' => array('value' => '150x50'),
          ),
      ),
      '#src' => $base_content_url . 'logo/44/Logo_150x50.gif',
      '#disabled' => TRUE,
    );

    $form['type_school']['logo_120x40'] = array(
      '#type' => 'image_button',
      '#title' => t("Sampe Logo"),
      '#description' => t('The logo to display'),
      '#states' => array(
        'visible' => array(
          ':input[name="show_school_logo"]' => array('checked' => TRUE),
          ':input[name="logo_size"]' => array('value' => '120x40'),
          ),
      ),
      '#src' => $base_content_url . 'logo/44/Logo_120x40.png',
      '#disabled' => TRUE,
    );

    $form['type_school']['logo_240x80'] = array(
      '#type' => 'image_button',
      '#title' => t("Sampe Logo"),
      '#description' => t('The logo to display'),
      '#states' => array(
        'visible' => array(
          ':input[name="show_school_logo"]' => array('checked' => TRUE),
          ':input[name="logo_size"]' => array('value' => '240x80'),
          ),
      ),
      '#src' => $base_content_url . 'logo/44/Logo_240x80.gif',
      '#disabled' => TRUE,
    );

    $form['type_program'] = array(
      '#type' => 'fieldset',
      '#title' => t("Program Diplay Items"),
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('value' => t('program')),
          ),
      ),
      '#description' => t('Please select program fields to display in listing.'),
      '#collapsible' => TRUE,
    );

    $form['type_program']['show_program_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show program title'),
      '#default_value' => empty($list['show_program_title']) ? 0 : $list['show_program_title'],
    );

    $form['type_program']['show_program_description'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show program description'),
      '#default_value' => empty($list['show_program_description']) ? 0 : $list['show_program_description'],
    );

    $form['buttons'] = array(
      '#type' => 'fieldset',
      '#title' => t("Buttons"),
      '#description' => t('Please select buttons to display in listing.'),
      '#collapsible' => TRUE,
    );

    $form['buttons']['degree_info'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Program Info button'),
      '#default_value' => empty($list['show_degree_info_button']) ? 0 : $list['show_degree_info_button'],
      '#states' => array(
        'visible' => array(
          ':input[name="listing_type"]' => array('!value' => 'school'),
          )
      ),
    );

    $form['buttons']['school_info'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Institution Info button'),
      '#default_value' => empty($list['show_school_info_button']) ? 0 : $list['show_school_info_button'],
    );

    $form['buttons']['request_info'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Request Info button'),
      '#default_value' => empty($list['show_request_info_button']) ? 0 : $list['show_request_info_button'],
    );

    $form['listing_display_type'] = array(
      '#type' => 'fieldset',
      '#title' => t("Display Type"),
      '#description' => t('Please select the display type of the listing.'),
      '#collapsible' => True,
      '#states' => array(
        'visible' => array(
          ':input[name="featured"]' => array('checked' => TRUE),
          )
      ),
    );

    $form['listing_display_type']['display_type'] = array(
      '#type' => 'radios',
      '#title' => t('Listing Display Type'),
      '#options' => array(
          'horizontal' => t('Horizontal'),
          'cube-design' => t('Vertical - cube design'),
      ),
      '#default_value' => empty($list['display_type']) ? 'horizontal' : $list['display_type'],
    );

    $form['advanced_rendering'] = array(
      '#type' => 'fieldset',
      '#title' => t("Advanced Rendering"),
      '#description' => t('Advanced rendering options.'),
      '#collapsible' => TRUE,
      //'#collapsed' => TRUE,
    );

    $form['advanced_rendering']['listing_in_html'] = array(
      '#type' => 'checkbox',
      '#title' => t('Render listings in the HTML on page load.'),
      '#default_value' => isset($list['listing_in_html']) ? $list['listing_in_html'] : 1,
      '#description' => t('If checked then the listing will load in the HTML when the server returns the first get. If not then there will be an empty <div> which is refreshed via AJAX.'),
    );

    return $form;

}


/**
 * Translates form fields to the correct DB column.
 */
function eddy_listings_fields($list){

	$fields = array();
	$fields['name'] = $list['listing_name'];

	$fields['featured'] = $list['featured'];
	$fields['description'] = $list['description'];
	$fields['show_school_title'] = $list['show_school_title'];
	$fields['show_school_description'] = $list['show_school_description'];
	$fields['show_school_logo'] = $list['show_school_logo'];
	$fields['show_pager'] = $list['show_pager'];
	$fields['random_item_from_list'] = 0;
    $fields['remove_capped'] = $list['remove_capped'];
    $fields['show_non_for_profit_list'] = $list['show_non_for_profit_list'];

	if ($list['featured'] == TRUE){
		if ($list['listing_type'] == 'program')
			$fields['featured_list'] = $list['featured_options_programs'];
		elseif ($list['listing_type'] == 'programs_by_school')
			$fields['featured_list'] = $list['featured_options_programs_by_school'];
		else
			$fields['featured_list'] = $list['featured_options_schools'];
	}else{
		$fields['featured_list'] = NULL;
	}

	if ($list['listing_type'] != 'program') {
		$fields['show_nested_programs'] = $list['show_nested_programs'];
		$fields['nested_record_count'] = $list['nested_record_count'];
		$fields['attach_list'] = $list['attach_list'];
		$fields['attached_list_id'] = $list['attached_list_id'];
	}

	$fields['filter_source'] = $list['filter_source'];

	if(!empty($list['include_types']) && is_array($list['include_types']) && array_sum($list['include_types']) > 0)
        $fields['include_types'] = serialize($list['include_types']);
	else
        $fields['include_types'] = serialize(array());

	if(!empty($list['include_campus_types']) && is_array($list['include_campus_types']) && array_sum($list['include_campus_types']) > 0)
        $fields['include_campus_types'] = serialize($list['include_campus_types']);
	else
        $fields['include_campus_types'] = serialize(array());

	$fields['online_when_empty'] = $list['online_when_empty'];

	if ($list['sort'] == 1) {

		$fields['sort'] = $list['sort'];

		if($list['listing_type'] != 'program')
			$fields['sort_by'] = $list['sort_school_by'];
		else
			$fields['sort_by'] = $list['sort_program_by'];

		if ($list['listing_type'] == 'program' && $list['sort_program_by'] != 'alphabetical') {
			$fields['group_by'] = $list['group_by'];
		}

	}else{
		$fields['sort'] = 0;
		$fields['sort_by'] = NULL;
		$fields['group_by'] = NULL;
	}

	$fields['show_pager_location'] = $list['show_pager_location'];
	$fields['user_change_records'] = $list['user_change_records'];

	if ($list['show_school_logo'] == 1) {
		$fields['logo_count'] = 'ALL';
		$fields['logo_size'] = $list['logo_size'];
	}

	$fields['type']	= $list['listing_type'];

	if ($list['listing_type'] == 'program') {
		$fields['show_program_title'] = $list['show_program_title'];
		$fields['show_program_description'] = $list['show_program_description'];
	}

	if ($list['listing_type'] == 'school') {
		$fields['show_nested_campuses'] = $list['show_nested_campuses'];
	}else{
		$fields['show_nested_campuses'] = 0;
	}

	$fields['show_degree_info_button'] = $list['degree_info'];
	$fields['show_school_info_button'] = $list['school_info'];
	$fields['show_request_info_button'] = $list['request_info'];
	$fields['total_records_to_display'] = $list['record_count'];

	if ($list['featured'] != TRUE)
		$fields['display_type'] = 'horizontal';
	else
		$fields['display_type'] = $list['display_type'];


    $fields['listing_in_html'] = $list['listing_in_html'];
    // $fields['prevent_empty_blocks'] = $list['prevent_empty_blocks'];

	return $fields;

}


/**
 * Callback function for validating the Machine Name.
 */
function listing_edit_machine_name_exists($value) {

    return db_query_range('SELECT 1 FROM {eddy_listing} WHERE machine_name = :listing', 0, 1, array(':listing' => $value))->fetchField();

}


/**
 * Gets all the Featured Lists from the Nexus DB.
 */
function eddy_listing_get_featured_list($listType){

    try {

        $options = array();

        if(!empty($listType)) {

            db_set_active('nexus');

            $query = db_select('FeatureList', 'f')
                ->fields('f', array('FeatureId', 'FeatureName'))
                ->condition('FeatureTypeId', $listType);

            $feature_results = $query->execute()->fetchAll();

            foreach ($feature_results as $feature) {
                $options[$feature->FeatureId] = $feature->FeatureName;

            }

            db_set_active();
        }

        return $options;

    }
    catch(Exception $e){

        db_set_active();
        if(module_exists('devel')){
            dpm($e);
        }

    }

}


/**
 * Gets the Campus Types indexed by the Nexus Id.
 */
function _eddy_listing_get_campus_types(){

	$options = array();

    //get the vocabulary id of "types"
	$query = db_select('taxonomy_vocabulary', 'v');
    $query->fields('v');
    $query->condition('name', 'tags');

    $vtype = $query->execute()->fetchAll();

    if(!empty($vtype) && isset($vtype[0]->vid)){

        $terms = taxonomy_get_tree($vtype[0]->vid);

        $termIds = array();

        foreach ((array)$terms as $index => $term){
            $termIds[$index] = $term->tid;
        }

        $values = taxonomy_term_load_multiple($termIds);

        foreach ((array)$values as $index => $value){
            if(isset($value->field_external_id['und'][0]['value'])){
                $options[$value->field_external_id['und'][0]['value']] = $value->name;
            }
        }

    }

	return $options;

}

#endregion