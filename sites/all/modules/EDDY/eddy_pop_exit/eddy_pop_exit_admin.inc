<?php

/**
 * @file
 * Administrative page callbacks for the Eddy Pop Exit Modulee.
 */


/**
 * Form callback which shows an overview page of all the custom Forms and their descriptions.
 */
function eddy_pop_exit_overview_page() {

    $result = eddy_pop_exit_db_call();

    $status_set ="none";
    $header = array(
      t('Title'),
      t('Description'),
      t('Type'),
      t('Trigger Type'),
      t('Created'),
      t('Changed'),
      t('Status'),
      t('Preview'),
      t('Operations'),
    );

    $rows = array();
    foreach ($result as $form) {

        if (!empty($form['changed'])) {
            $date_changed = format_date($form['changed']);
        }
        else {
            $date_changed = 'Has never been updated';
        }

        $trigger_type = "Exit";
        if(isset($form['trigger_type'])){

            switch($form['trigger_type']){

                case 'exit':
                    $trigger_type = "Exit";
                    break;
                case 'leave_behind':
                    $trigger_type = "Leave Behind";
                    break;

            }

        }else{

            $form['trigger_type'] = 'exit';

        }

        if($form['active'] == 1) {
            $status = '<b>Active</b>';
            $edit_text = l(t('Edit'), 'admin/structure/eddy_pop_exit/manage/' . $form['id'] . '/edit') . " |  ".  t('<b>Active</b>');
            $class = 'active_pop';

            if($form['trigger_type'] == 'leave_behind'){
                $class = 'active_leave_behind';
            }

            $status_set = 'active';
        }

        else{
            $status = 'Not Active';
            $edit_text = l(t('Edit'), 'admin/structure/eddy_pop_exit/manage/' . $form['id'] . '/edit') . " | ".  l(t('Make Active'), 'admin/structure/eddy_pop_exit/set_pop_up/' . $form['id'] . '/' . $form['trigger_type']);
            $class = 'not_active_pop';
        }

        if ($form['type'] == 'iframe_add'){
            $preview = t('Not Available');
            $form['type'] = t('IFrame');
        }
        else {
            $form['type'] = 'HTML';
            $preview = l(t('Preview'), 'eddy_pop_exit/' .$form['id'], array('attributes'=>array('target'=>'_blank')));
        }

        $rows[] = array(
           'data' => array(
              'title' => $form['title'],
              'description' => $form['description'],
              'type' => $form['type'],
              'trigger_type' => $trigger_type,
              'Created' => format_date($form['created']),
              'Changed' => $date_changed,
              'Status' => $status,
              'Preview' => $preview,
              'edit' => $edit_text,
          ),
          'class' => array($class),
        );
    }
    if ($status_set == 'none'){
        drupal_set_message(t('There are no active pop exits please choose one'));
    }

    $desctipion = "On this form you can edit your Pop Ups and Select which one is active. ";
    $desctipion = "<p>" . $desctipion . "</p>";

    $theme = $desctipion . theme('table', array('header' => $header, 'rows' => $rows));



    return $theme;
}

/**
 * Implements hook_().
 * for configuring the module
 */
function eddy_pop_exit_form($form, &$form_state, $form_value = 0) {

    $type = 'html';
    $disabled = FALSE;
    $type_options =  array(
        'html' => t('HTML'),
        'iframe_info' => t('IFrame'),
      );


    if (isset($form_value['type'])) {
        $disabled = TRUE;
        if ($form_value['type'] == 'iframe_add') {
            $type = 'iframe_info';
            $type_options=  array(
                 'iframe_info' => t('IFrame'));
        }
        else{
            $type_options =  array(
                'html' => t('HTML'));
        }
    }

    $form['exit_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#required' => true,
      '#default_value' => empty($form_value['title']) ? '' : $form_value['title'],
    );

    $form['exit_description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#default_value' => empty($form_value['description']) ? '' : $form_value['description'],
    );

    $form['trigger_type'] = array(
      '#type' => 'select',
      '#options' => array('exit' => 'Exit', 'leave_behind' => 'Leave behind'),
      '#title' => t('How Would you link the Ad to Trigger?'),
      '#default_value' => (isset($form_value['trigger_type'])) ? $form_value['trigger_type'] : 'exit',
      '#disabled' => $disabled,
    );

    $form['exit_type'] = array(
      '#type' => 'radios',
      '#options' => $type_options,
      '#title' => t('What type of Pop Exit?'),
      '#default_value' => $type,
      '#disabled' => $disabled,
    );

    $form['has_container'] = array(
      '#type' => 'radios',
      '#options' => array( 0 => 'No', 1 => 'Yes'),
      '#title' => t('Do you want to include the site Container'),
      '#default_value' => (isset($form_value['has_container'])) ? $form_value['has_container'] : 0,

    );

    $form['html_text'] = array(
      '#type' => 'textarea',
      '#title' => t('Enter the HTML here'),
      '#default_value' => empty($form_value['html']) ? '' : $form_value['html'],
      '#states' => array(
        'visible' => array(
          ':input[name="exit_type"]' => array('value' => 'html'),
        ),
        'required' => array(
          ':input[name="exit_type"]' => array('value' => 'html'),
        ),
      ),
    );

    $num_items = 1;
    if (isset($form_value['settings'])){
        $form_value['settings'] = unserialize($form_value['settings']);
        $default_value =  $form_value['settings']['sets'];
    }

    if($form_value != 0){
        $num_items = count($default_value);
    }

    $form['#tree'] = true;
    $form['iframe_fields']['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Url'),
      '#maxlength' => 255,
      '#size' => 100,
      '#default_value' => empty($form_value['url']) ? '' : $form_value['url'],
       '#states' => array(
        'visible' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
        'required' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
      ),
    );


    $form['iframe_fields']['sets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Connection Settings'),
      '#prefix' => '<div id="sets-wrapper">',
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
      ),
    );

    if (!array_key_exists('num_items', $form_state)) {
        $form_state['num_items'] = $num_items;
    }

    for ($i = 0; $i < $form_state['num_items']; $i++)
    {
        $form['iframe_fields']['sets'][$i] = eddy_pop_exit_form_fieldset($form_state, $i, $form_value);
    }

    $form['add_another'] = array(
      '#type' => 'button',
      '#validate' => array('eddy_pop_exit_form_add_item'),
      '#value' => 'Add Another',
      '#ajax' => array(
        'callback' => 'eddy_pop_exit_form_add_item_ajax',
        'wrapper' => 'sets-wrapper',
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
      ),
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => 'Save');

    return $form;

}



function eddy_pop_exit_form_fieldset(&$form_state, $index, $form_value) {

    $default_value =  $form_value['settings']['sets'];
    $fieldset = array(
      '#type' => 'fieldset',
    );

    $fieldset['field_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Field'),
      '#description' => t('The field name i.e.key'),
      '#default_value' => empty($default_value[$index]->name) ? '' : $default_value[$index]->name,
      '#states' => array(
        'required' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
      ),
    );

    $fieldset['field_key_value'] = array(
      '#type' => 'textfield',
      '#title' => t('Field Value'),
      '#description' => t('The field value i.e.5161515 the following dynamic values can be sent to [area_interest] , [session_id] , [track_id]'),
      '#states' => array(
        'required' => array(
          ':input[name="exit_type"]' => array('value' => 'iframe_info'),
        ),
      ),
      '#default_value' =>empty($default_value[$index]->value)  ? '' : $default_value[$index]->value,
    );

    if ($form_state['num_items'] > 1) {
        $fieldset['remove'] = array(
          '#type' => 'button',
          '#validate' => array('eddy_pop_exit_form_remove'),
          '#value' => t('Remove'),
          '#name' => $index,
          '#ajax' => array(
            'callback' => 'eddy_pop_exit_form_add_item_ajax',
            'wrapper' => 'sets-wrapper',
          ),
          '#limit_validation_errors' => array(),
        );
    }

    return $fieldset;
}

function eddy_pop_exit_form_remove($form, &$form_state) {
    $trigger = $form_state['triggering_element'];

    if ($form_state['num_items'] > 1) {
        $form_state['num_items'] --;
        $form_state['rebuild'] = true;
        unset($form_state['input']['sets'][$trigger['#name']]);
        $form_state['input']['iframe_fields']['sets'] = array_values($form_state['input']['iframe_fields']['sets']);
    }
}

function eddy_pop_exit_form_add_item($form, &$form_state) {
    $form_state['num_items'] ++;
    $form_state['rebuild'] = true;
}

function eddy_pop_exit_form_add_item_ajax($form, $form_state) {
    return $form['iframe_fields']['sets'];
}

function eddy_pop_exit_form_validate(&$form, &$form_state) {

    $url = $form_state['values']['iframe_fields']['url'];

    if ((preg_match('/^http(s)?:\/\//', $url) == 0) && (!empty($url))) {
        form_set_error('url', $url . t(' is an invalid URL, Urls must start with an http: or https: please try again. i.e. http://www.google.com'));
    }
    return;
}

function eddy_pop_exit_form_submit($form, &$form_state) {

    $form_values = $form_state['values'];

    eddy_pop_exit_save($form_values);

    $form_state['redirect'] = 'admin/structure/eddy_pop_exit/manage';

    drupal_set_message(t('The EDDY Exit Pop settings have been saved.'));
}

function eddy_pop_exit_save($form_values) {
    $fields = eddy_pop_exit_fields($form_values);

    try {
        $result = TRUE;

        $field = db_insert('eddy_pop')
            ->fields($fields)
            ->execute();
        if($fields['type'] != 'html_text'){
            $fields['settings'] = unserialize($fields['settings']);
        }

        //$form_engine['id'] = $field;

        drupal_set_message(t('Your configuration has been saved.'));

        cache_clear_all();
    }
    catch (Exception $e) {
        drupal_set_message(t('There was an issue with your configuration.'));
        dsm($e);
    }
}

function eddy_pop_exit_fields($form_values) {
    /* Set up the array of fields to insert into the database.
     *  Skipping the fields that are unneccessary to save the values for.
     */
    $fields = array();
    $fields['title'] = $form_values['exit_name'];
    $fields['description'] = $form_values['exit_description'];
    $fields['trigger_type'] = $form_values['trigger_type'];
    $fields['has_container'] = $form_values['has_container'];

    if (!empty($form_values['html_text'])) {
        $fields['type'] = 'html_text';
        $fields['html'] = $form_values['html_text'];
        $fields['created'] = time();
    }
    else {
        $fields['type'] = 'iframe_add';
        $values = $form_values['iframe_fields']['sets'];
        $index = 0;

        $dynamic_fields['sets'] = array();

        foreach ($values as $value) {

            $dynamic_fields['sets'][$index] = new stdclass;
            $dynamic_fields['sets'][$index]->name = $value['field_key'];
            $dynamic_fields['sets'][$index]->value = $value['field_key_value'];

            $index++;

        }
        $fields['url'] = $form_values['iframe_fields']['url'];
        $fields['created'] = time();
        $fields['settings'] = serialize($dynamic_fields);
        $fields['created'] = time();

    }
    return $fields;
}

/**
 * Form callback; Build the form that handles the editing of a form.
 */
function eddy_pop_exit_edit_form($form, &$form_state, $type, $form_value_id) {
    $form_value = eddy_pop_exit_load($form_value_id);

    $form = eddy_pop_exit_form($form, $form_state, $form_value);
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['update'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('eddy_pop_exit_edit_form_update'),
    );

    //custom forms may be deleted.`
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#access' => $type == 'edit',
      '#submit' => array('eddy_pop_exit_delete_submit'),
    );

    return $form;
}

///**
// * Form callback; To update forms
// */
function eddy_pop_exit_edit_form_update($form, &$form_state) {
    $form_id = $form_state['build_info']['args'][1]; //retrieves the id of the list you are editing
    $form_values = $form_state['values'];
    $fields = eddy_pop_exit_fields($form_values, 'update');

    $fields['changed'] = time();

    try {
        $records_updated = db_update('eddy_pop')
            ->fields($fields)
            ->condition('id', $form_id)
            ->execute();

        if ($records_updated > 0) {
            drupal_set_message(t('Your configuration has been saved.'));

            $form_state['redirect'] = 'admin/structure/eddy_pop_exit/manage';
        }
        else {
            drupal_set_message(t('No updates were made, please make sure you have edited a field.'), 'warning');
        }
    }
    catch (Exception $e) {
        drupal_set_message(t('There was an error.'), 'error');
        dsm($e);
    }
}

/**
 * Submit function for the 'Delete' button on the form engine editing form.
 */
function eddy_pop_exit_delete_submit($form, &$form_state) {
    $form_state['redirect'] = 'admin/structure/eddy_pop_exit/manage/' . $form_state['build_info']['args'][1] . '/delete';
}

/**
 * Form callback; Get a confirm form for deletion of a custom form.
 */
function eddy_pop_exit_delete_form_page($form_id) {
    return drupal_get_form('eddy_pop_exit_delete_form_confirm', $form_id);
}

/**
 * Build a confirm form for deletion of a custom form engine.
 */
function eddy_pop_exit_delete_form_confirm($form, &$form_state, $form_id) {
    $form_engine = eddy_pop_exit_load($form_id);
    $form['#form_engine'] = $form_engine;
    $caption = '<p>' . t('This action cannot be undone.') . '</p>';
    return confirm_form($form, t('Are you sure you want to delete this form: %name?', array('%name' => $form_engine['title'])), 'admin/structure/eddy_pop_exit/manage/' . $form_engine['id'], $caption, t('Delete'));
}

/**
 * Delete a custom form.
 */
function eddy_pop_exit_delete_form_confirm_submit($form, &$form_state) {
    $form_engine = $form['#form_engine'];
    $form_state['redirect'] = 'admin/structure/eddy_pop_exit';

    // Delete the custom form.
    eddy_pop_exit_delete($form_engine);
}

/**
 * Delete a custom form.
 */
function eddy_pop_exit_delete($form_engine) {
    $result = db_query('SELECT * FROM {eddy_pop} WHERE NOT id=:id', array(':id' => $form_engine['id']))->fetchObject();
    if (empty($result)) {
        form_set_error('Form Validation', t('At least one form needs to exist, therefore you cannot delete this form at this time.'));
        return;
    }
    else {

        // Delete the Form.
        db_delete('eddy_pop')
            ->condition('id', $form_engine['id'])
            ->execute();

        cache_clear_all();
        module_invoke_all('eddy_pop_exit', $form_engine);
    }
}


/**
 * Form callback; Build the form that handles the editing of a form.
 */
function eddy_pop_exit_edit_container_form($form, &$form_state, $type) {

    $form_value = eddy_pop_exit_container_load('default');
    $form = eddy_pop_exit_container_form($form, $form_state, $form_value);
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['update'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('eddy_pop_exit_edit_container_form_update'),
    );



    return $form;

}


/**
 * Implements hook_().
 * for configuring the module
 */
function eddy_pop_exit_container_form($form, &$form_state, $form_value = 0) {

    $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#required' => true,
      '#default_value' => empty($form_value['title']) ? '' : $form_value['title'],
       '#disabled' => true
    );

    $form['custom_head'] = array(
  '#type' => 'textarea',
  '#title' => t('Enter the custom head tags here'),
  '#default_value' => empty($form_value['custom_head']) ? '' : $form_value['custom_head']
);

    $form['custom_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter the custom css here'),
    '#default_value' => empty($form_value['custom_css']) ? '' : $form_value['custom_css']
  );

    $form['header_mark_up'] = array(
      '#type' => 'textarea',
      '#title' => t('Enter the Header HTML here'),
      '#default_value' => empty($form_value['header_mark_up']) ? '' : $form_value['header_mark_up']
    );



    $form['footer_mark_up'] = array(
     '#type' => 'textarea',
     '#title' => t('Enter the Footer HTML here'),
     '#default_value' => empty($form_value['footer_mark_up']) ? '' : $form_value['footer_mark_up']
   );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => 'Save');

    return $form;

}

function eddy_pop_exit_container_fields($form_values) {
    /* Set up the array of fields to insert into the database.
     *  Skipping the fields that are unneccessary to save the values for.
     */
    $fields = array();
    $fields['title'] = $form_values['title'];
    $fields['custom_head'] = $form_values['custom_head'];
    $fields['custom_css'] = $form_values['custom_css'];
    $fields['header_mark_up'] = $form_values['header_mark_up'];

    $fields['footer_mark_up'] = $form_values['footer_mark_up'];
    $fields['created'] = time();

    $fields['created'] = time();


    return $fields;
}


function eddy_pop_exit_edit_container_form_update($form, &$form_state) {
    $form_id = $form_state['build_info']['args'][1]; //retrieves the id of the list you are editing
    $form_values = $form_state['values'];
    $fields = eddy_pop_exit_container_fields($form_values, 'update');

    $fields['changed'] = time();

    try {
        $records_updated = db_update('eddy_pop_containers')
            ->fields($fields)
            ->condition('title', 'default')
            ->execute();

        if ($records_updated > 0) {
            drupal_set_message(t('Your configuration has been saved.'));

            $form_state['redirect'] = 'admin/structure/eddy_pop_exit/manage';
        }
        else {
            drupal_set_message(t('No updates were made, please make sure you have edited a field.'), 'warning');
        }
    }
    catch (Exception $e) {
        drupal_set_message(t('There was an error.'), 'error');
        dsm($e);
    }
}

