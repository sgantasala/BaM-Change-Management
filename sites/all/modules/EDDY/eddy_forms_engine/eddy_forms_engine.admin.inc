<?php

/**
 * @file
 * Administrative page callbacks for Forms Engine module.
 */

/**
 * Form callback which shows an overview page of all the custom Forms and their descriptions.
 */
function eddy_forms_engine_overview_page() {

    $result = db_query("SELECT * FROM {eddy_forms_engine} ORDER BY name", array(), array('fetch' => PDO::FETCH_ASSOC));

    $header = array(
      t('Title'),
      t('Description'),
      t('Rendering Type'),
      t('Rendering Strategy'),
      t('Published'),
      t('Operations'),
    );

    $rows = array();
    foreach ($result as $form) {
        $rows[] = array(
            'title' => $form['name'],
            'description' => $form['description'],
            'rendering_type' => $form['rendering_type'],
            'rendering_strategy' => $form['rendering_strategy'],
            'published' => $form['published'],
            'edit' => l(t('config Form'), 'admin/structure/eddy_forms_engine/manage/' . $form['id'] . '/edit'),
        );
    }

    return theme('table', array('header' => $header, 'rows' => $rows));

}

/**
 * Returns HTML for a Form title, Rendering Strategy of the form and description for the Forms Engine overview page.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: The Forms's title.
 *   - rendering strategy: The Form's rendering strategy.
 *   - description: The Form's description.
 *
 */
function theme_eddy_forms_engine_admin_overview($variables) {
    $output = check_plain($variables['title']);
    $output .= '<div class="description">Rendering Strategy: ' . filter_xss_admin($variables['rendering_strategy']) . '</div>';
    $output .= '<div class="description">' . filter_xss_admin($variables['description']) . '</div>';

    return $output;
}

/**
 * Form callback; Build the form that handles the adding of a form.
 */

function eddy_forms_engine_add_form($form, &$form_state, $form_engine = array()) {

    $form = eddy_forms_engine_form($form, $form_state, $form_engine);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    return $form;
}

/**
 * Form callback; Build the form that handles the editing of a form.
 */
function eddy_forms_engine_edit_form($form, &$form_state, $type, $form_engine_id) {
    $form_engine = eddy_forms_engine_load($form_engine_id);

    $form = eddy_forms_engine_form($form, $form_state, $form_engine);

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['update'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('eddy_forms_engine_edit_form_update'),
    );

    //custom forms may be deleted.
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#access' => $type == 'edit',
      '#submit' => array('eddy_forms_engine_delete_submit'),
    );

    return $form;
}

function eddy_forms_engine_edit_form_update($form, &$form_state) {
	$form_id = $form_state['build_info']['args'][1]; //retrieves the id of the list you are editing
	$form_values = $form_state['values'];

	$fields  = eddy_form_engine_fields($form_values, 'update');

	try {
		$records_updated = db_update('eddy_forms_engine')
			->fields($fields)
			->condition('id', $form_id)
			->execute();

		if ($fields['published'] == 1) {
			$num_updated = db_update('eddy_forms_engine')
			->fields(array('published' => 0,))
			->condition('id', $form_id, '<>')
			->execute();

			variable_set('eddy_forms_engine_published_form_id', $form_id);
		}

		if ($records_updated > 0) {
			drupal_set_message(t('Your configuration has been saved.'));
		}
		else{
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
function eddy_forms_engine_delete_submit($form, &$form_state) {
	$form_state['redirect'] = 'admin/structure/eddy_forms_engine/manage/'.$form_state['build_info']['args'][1].'/delete';
}

/**
 * Form callback; Get a confirm form for deletion of a custom form.
 */
function eddy_forms_engine_delete_form_page($form_id) {
	return drupal_get_form('eddy_forms_engine_delete_form_confirm', $form_id);
}


/**
 * Build a confirm form for deletion of a custom form engine.
 */
function eddy_forms_engine_delete_form_confirm($form, &$form_state, $form_id) {
	$form_engine = eddy_forms_engine_load($form_id);
	$form['#form_engine'] = $form_engine;
	$caption = '<p>' . t('This action cannot be undone.') . '</p>';
	return confirm_form($form, t('Are you sure you want to delete this form: %name?', array('%name' => $form_engine['name'])), 'admin/structure/eddy_forms_engine/manage/' . $form_engine['id'], $caption, t('Delete'));
}

/**
 * Delete a custom form.
 */

function eddy_forms_engine_delete_form_confirm_submit($form, &$form_state) {
	$form_engine = $form['#form_engine'];
	$form_state['redirect'] = 'admin/structure/eddy_forms_engine';

	// Delete the custom form.
	eddy_forms_engine_delete($form_engine);

}

/**
 * Delete a custom form.
 */
function eddy_forms_engine_delete($form_engine) {
    $result = db_query('SELECT * FROM {eddy_forms_engine} WHERE NOT id=:id', array(':id' => $form_engine['id']))->fetchObject();
	if (empty($result)) {
		form_set_error('Form Validation', t('At least one form needs to exist, therefore you cannot delete this form at this time.'));
		return;
	}
	else {
		$id_updated = db_update('eddy_forms_engine')
			->fields(array('published' => 1,))
			->condition('id', $result->id, '=')
			->execute();

		variable_set('eddy_forms_engine_published_form_id', $result->id);

		// Delete the Form.
		db_delete('eddy_forms_engine')
			->condition('id', $form_engine['id'])
			->execute();

		cache_clear_all();
		module_invoke_all('eddy_forms_engine_delete', $form_engine);
	}
}


function eddy_forms_engine_form($form, &$form_state, $form_engine){

    $form['form_name'] = array(
      '#type' => 'textfield',
      '#title' => t("Form Name"),
      '#required' => TRUE,
      '#default_value' => empty($form_engine['name']) ? '' : $form_engine['name'],
    );

    if(count($form_engine) == 0){
        $form['machine_name'] = array(
          '#type' => 'machine_name',
          '#title' => t('Machine Name'),
          '#default_value' => '',
          '#maxlength' => 128,
          '#description' => t('A unique name for a Form.'),
          '#machine_name' => array(
            'exists' => 'form_edit_machine_name_exists',
            'source' => array('form_name'),
            'label' => t('Machine Name'),
            'replace_pattern' => '[^a-z0-9-]+',
            'replace' => '-',
          ),
        );
    }

    $form['published'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use on Program Template pages.'),
      '#default_value' => (!array_key_exists("published",$form_engine))? '' : (empty($form_engine['published']) ? 0 : $form_engine['published']),
      '#description' => t('This form will be used on all the Program Template pages. Please do not check this box unless you would like this configuration to be used on the entire site.'),
    );

    $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => (!array_key_exists("description",$form_engine))? '' : (empty($form_engine['description']) ? '' : $form_engine['description']),
    );

    $form['form_attributes'] = array(
      '#type' => 'fieldset',
      '#title' => t("Form Attributes"),
      '#description' => t('Please set the attributes desired for the form.'),
      '#collapsible' => FALSE,
    );

    $form['form_attributes']['rendering_type'] = array(
      '#type' => 'select',
      '#title' => t("Rendering Type:"),
      '#options' => array(
          '' => '-- Select Rendering Type --',
          'program-template' => 'Program Template',
          'program-wizard' => 'Program Wizard',
          'wizard' => 'Wizard',

      ),
      '#default_value' => (!array_key_exists("rendering_type",$form_engine))? '' : (empty($form_engine['rendering_type']) ? '' : $form_engine['rendering_type']),
      '#required' => TRUE,
      '#ajax' => array(
        'callback' => 'change_rendering_strategies_templates',
        'wrapper' => array('rendering_strategy_container', 'templates_container'),
       ),
    );

    $form['form_attributes']['rendering_strategy'] = array(
      '#type' => 'select',
      '#title' => t("Rendering Strategy:"),
      '#options' => get_rendering_strategies_load($form, $form_state),
      '#default_value' => (!array_key_exists("rendering_strategy",$form_engine))? '' : (empty($form_engine['rendering_strategy']) ? '' : $form_engine['rendering_strategy']),
      '#required' => TRUE,
      '#prefix' => '<div id="rendering_strategy_container">',
      '#suffix' => '</div>',
      '#ajax' => array(
          'callback' => 'change_form_skin',
          'wrapper' => 'rendering_strategy_skin',
      ),
    );
    $form['form_attributes']['header_arrows_included'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show previous and continue arrows in the form header (for mobile only).'),
      '#default_value' => array_key_exists("header_arrows_included",$form_engine) ? $form_engine['header_arrows_included'] : 1,
      '#states' => array(
        'visible' => array(
            ':input[name="rendering_strategy"]' => array('value' => 'WIZARDPROFESSIONALBOOTSTRAP'),
        ),
      ),
    );


    //form_template states visible won't work when its options trigger by ajax call.
    //solution is add a wrapper container
    $form['form_attributes']['template_wrapper'] = array(
        '#type' => 'container',
        '#states' => array(
            'visible' => array(
                ':input[name="rendering_type"]' => array('!value' => 'program-template'),
            ),
        )
    );
    $form['form_attributes']['template_wrapper']['form_template'] = array(
      '#type' => 'select',
      '#title' => t("Form Template:"),
      '#options' => landingpages_get_wizard_form_template($form, $form_state),
      '#default_value' => (!array_key_exists("form_template",$form_engine))? '' : (empty($form_engine['form_template']) ? '' : $form_engine['form_template']),
      // '#required' => TRUE, // required only when rendering_type is wizard
      '#prefix' => '<div id="templates_container">',
      '#suffix' => '</div>',
      '#states' => array(
       'required' => array(
            ':input[name="rendering_type"]' => array('!value' => 'program-template'),
        ),
      ),
    );

    $form['form_attributes']['form_skin'] = array(
      '#type' => 'select',
      '#title' => t("Form Skin:"),
      '#options' => landingpages_get_form_engine_skins($form, $form_state),
      '#default_value' => (!array_key_exists("form_skin",$form_engine))? '' : (empty($form_engine['form_skin']) ? '' : $form_engine['form_skin']),
      '#required' => TRUE,
      '#prefix' => '<div id="rendering_strategy_skin">',
      '#suffix' => '</div>',
      '#states' => array(
        'visible' => array(
            ':input[name="rendering_strategy"]' => array('!value' => ''),
            ),
       ),
    );

    $form['form_attributes']['form_custom_attributes'] = array(
     '#type' => 'textarea',
     '#title' => t('Additional Custom Attributes'),
     '#description' => t('Custom scripts will be attached and rendered to the FormsEngine object'),
     '#default_value' => (!array_key_exists("form_custom_attributes",$form_engine))? '' : (empty($form_engine['form_custom_attributes']) ? '' : $form_engine['form_custom_attributes']),
    );

    $form['workflow_redirect'] = array(
		'#type' => 'fieldset',
		'#title' => t('Form Workflow Redirects'),
		//'#weight' => 1,
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);

	$form['form_content'] = array(
		'#type' => 'fieldset',
		'#title' => t('Form Page content'),
		//'#weight' => 0,
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);

	$form['thank_you_content'] = array(
		'#type' => 'fieldset',
		'#title' => t('Thank You Page content'),
		//'#weight' => 1,
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
	);

	$form['form_content']['facts'] = array(
		'#type' => 'textarea',
		'#title' => t('Facts Body'),
		'#default_value' => (!array_key_exists("facts",$form_engine))? '' : (empty($form_engine['facts']) ? '' : $form_engine['facts']),//variable_get('eddy_forms_engine_global_facts'),
		//'#rows' => 6,
		'#description' => t('This fact is going to display on each Program Template if there is no Student Quotes.'),
		//'#weight' => -8,
	);

	$form['form_content']['further_info'] = array(
		'#type' => 'textarea',
		'#title' => t('Further Info Body'),
		'#default_value' => (!array_key_exists("further_info",$form_engine))? '' : (empty($form_engine['further_info']) ? '' : $form_engine['further_info']),//variable_get('eddy_forms_engine_further_info'),
		//'#rows' => 6,
		'#description' => t('[school-name] will be replaced to the current school name on the form page.'),
		//'#weight' => -7,
	);
	$form['form_content']['program_template_message'] = array(
        '#type' => 'text_format',
        '#title' => t('Program Template Message'),
        '#format' => 'full_html',
        '#default_value' => (!array_key_exists("program_template_message",$form_engine))? '' : (empty($form_engine['program_template_message']) ? '' : $form_engine['program_template_message']),//variable_get('program_template_msg'),
        '#description' => t('This message will be displayed on top of each Program Template page.'),
    );

	$form['thank_you_content']['thank_you_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Thank You Page title'),
		'#default_value' => (!array_key_exists("thank_you_title",$form_engine))? '' : (empty($form_engine['thank_you_title']) ? '' : $form_engine['thank_you_title']),//variable_get('thank_you_title'),
		'#description' => t('The title that will appear in the &#60;title&#62; tag in the &#60;head&#62; of the page.'),
		//'#weight' => -6,
	);

	$form['thank_you_content']['thank_you_success_message'] = array(
		'#type' => 'text_format',
		'#title' => t('Thank you page successful lead message body:<br><i>[user-name] will be replaced to the current user&rsquo;s name on the thank you page.</i>'),
		'#format' => 'full_html',
		'#default_value' => (!array_key_exists("thank_you_success_message",$form_engine))? '' : (empty($form_engine['thank_you_success_message']) ? '' : $form_engine['thank_you_success_message']),//variable_get('thank_you_success_lead_msg'),
		//'#description' => t('[user-name] will be replaced to the current user&rsquo;s name on the form page.'),
		//'#weight' => -5,
	);

	$form['thank_you_content']['thank_you_failed_message'] = array(
		'#type' => 'text_format',
		'#title' => t('Thank you page failed lead message body:<br><i>[user-name] will be replaced to the current user&rsquo;s name on the thank you page.</i>'),
		'#format' => 'full_html',
		'#default_value' => (!array_key_exists("thank_you_failed_message",$form_engine))? '' : (empty($form_engine['thank_you_failed_message']) ? '' : $form_engine['thank_you_failed_message']),//variable_get('thank_you_failed_lead_msg'),
		'#rows' => 6,
		//'#description' => t('[user-name] will be replaced to the current user&rsquo;s name on the form page.'),
	);

    $form['thank_you_content']['set_yourself_up'] = array(
         '#type' => 'text_format',
         '#title' => t('Set yourself up for success body'),
         '#default_value' => (!array_key_exists("set_yourself_up",$form_engine))? '' : (empty($form_engine['set_yourself_up']) ? '' : $form_engine['set_yourself_up']),
         '#format' => 'full_html',
         '#rows' => 6,
         //'#weight' => -3,
     );

	$form['thank_you_content']['tuition_tips'] = array(
		'#type' => 'text_format',
		'#title' => t('Tuition tips body'),
		'#default_value' => (!array_key_exists("tuition_tips",$form_engine))? '' : (empty($form_engine['tuition_tips']) ? '' : $form_engine['tuition_tips']),
		'#format' => 'full_html',
		'#rows' => 6,
		//'#weight' => -2,
	);

	$form['thank_you_content']['student_guide'] = array(
		'#type' => 'text_format',
		'#title' => t('Student guide'),
		'#default_value' =>  (!array_key_exists("student_guide",$form_engine))? '' : (empty($form_engine['student_guide']) ? '' : $form_engine['student_guide']),
		'#format' => 'full_html',
		'#rows' => 6,
		//'#weight' => -1,
	);

	$form['workflow_redirect']['workflow_start_redirect'] = array(
		'#type' => 'textfield',
		'#title' => t('Start Page redirect'),
		'#default_value' => (!array_key_exists("workflow_start_redirect",$form_engine))? '' : (empty($form_engine['workflow_start_redirect']) ? '' : ($form_engine['workflow_start_redirect']=='<front>')? $form_engine['workflow_start_redirect']: drupal_lookup_path('alias',$form_engine['workflow_start_redirect'])),
		'#description' => t('Get the URL from "Form Redirect Content Page" content type.'),
	);

	$form['workflow_redirect']['workflow_managedchoice_redirect'] = array(
		'#type' => 'textfield',
		'#title' => t('Managed Choice Page redirect'),
		'#default_value' => (!array_key_exists("workflow_managedchoice_redirect",$form_engine))? '' : (empty($form_engine['workflow_managedchoice_redirect']) ? '' : drupal_lookup_path('alias',$form_engine['workflow_managedchoice_redirect'])),
		'#description' => t('Get the URL from "Form Redirect Content Page" content type.'),
	);

	$form['workflow_redirect']['workflow_thankyou_redirect'] = array(
		'#type' => 'textfield',
		'#title' => t('Thank You Page redirect'),
		'#default_value' => (!array_key_exists("workflow_thankyou_redirect",$form_engine))? '' : (empty($form_engine['workflow_thankyou_redirect']) ? '' : drupal_lookup_path('alias',$form_engine['workflow_thankyou_redirect'])),
		'#description' => t('Get the URL from "Form Redirect Content Page" content type.'),
	);
    $form['workflow_redirect']['workflow_nomatch_redirect'] = array(
        '#type' => 'textfield',
        '#title' => t('No Match Page redirect'),
        '#default_value' => (!array_key_exists("workflow_nomatch_redirect",$form_engine))? '' : (empty($form_engine['workflow_nomatch_redirect']) ? '' : drupal_lookup_path('alias',$form_engine['workflow_nomatch_redirect'])),
        '#description' => t('Get the URL from "Form Redirect Content Page" content type.'),
    );
    $form['#validate'][] = '_eddy_forms_engine_form_validate';

    return $form;

}

/**
 * Form validation to check if form template is selected for Wizard rendering type.
 */
function _eddy_forms_engine_form_validate($form, &$form_state){
    if ($form_state['values']['rendering_type'] != 'program-template' && empty($form_state['values']['form_template'])) {
        form_set_error('form_template', t('Form Template: field is required.'));
    }

}

function form_edit_machine_name_exists($value) {
    // Checks for unique name.
    $custom_exists = db_query_range('SELECT 1 FROM {eddy_forms_engine} WHERE machine_name = :form', 0, 1, array(':form' => $value))->fetchField();
    return $custom_exists;
}


function landingpages_get_wizard_form_template($form, $form_state){

    $options = array('' => '-- Select Template --');

    if ((isset($form_state['values']) && !empty($form_state['values']['rendering_type'])) || !empty($form['form_attributes']['rendering_type']['#default_value'])) {

        //ProgramTemplate = 1, WizardTemplate = 2, ProgramWizard = 3
		if(isset($form_state['values'])){
			if($form_state['values']['rendering_type'] == 'program-template')
				$type = 1;
			elseif($form_state['values']['rendering_type'] == 'wizard')
				$type = 2;
            else
                $type = 3;

		}elseif(!empty($form['form_attributes']['rendering_type']['#default_value'])){
			if($form['form_attributes']['rendering_type']['#default_value'] == 'program-template')
				$type = 1;
			elseif($form['form_attributes']['rendering_type']['#default_value'] == 'wizard')
				$type = 2;
            else
                $type = 3;
		}
        $request = drupal_http_request(_eddy_form_engine_get_form_domain_for_server_side_calls() . "/TemplateManager/GetTemplateListByType?FormTemplateType=" . $type . "&callback=an");
        $jsonInput = str_replace(');','',str_replace('an(','',$request->data));
        $decoded = json_decode($jsonInput, true);

        foreach ($decoded as $key => $value) {
            $options[$value['TemplateId']] = $value['TemplateName'];
        }
    }
	return $options;

}


function get_rendering_strategies_load($form, $form_state) {

	//$strategies = &drupal_static(__FUNCTION__);

    $strategies = array('' => '-- Select Rendering Strategy --');

	if ((isset($form_state['values']) && !empty($form_state['values']['rendering_type'])) || !empty($form['form_attributes']['rendering_type']['#default_value'])) {

        //ProgramTemplate = 1, WizardTemplate = 2, ProgramWizard = 3
		if(isset($form_state['values'])){
			if($form_state['values']['rendering_type'] == 'program-template')
				$type = 1;
			elseif($form_state['values']['rendering_type'] == 'wizard')
				$type = 2;
            else
                $type = 3;

		}elseif(!empty($form['form_attributes']['rendering_type']['#default_value'])){
			if($form['form_attributes']['rendering_type']['#default_value'] == 'program-template')
				$type = 1;
			elseif($form['form_attributes']['rendering_type']['#default_value'] == 'wizard')
				$type = 2;
            else
                $type = 3;
		}

		$request = drupal_http_request(_eddy_form_engine_get_form_domain_for_server_side_calls() . '/TemplateManager/GetRenderingStrategiesByType?FormTemplateType=' . $type . '&callback=jsonCallback');

		$jsonInput = str_replace(');','',str_replace('jsonCallback(','',$request->data));
		$decoded = json_decode($jsonInput, true);

		foreach ($decoded as $key => $value) {
			$strategies[$value['Name']] = $value['Name'];
		}

	}

	return $strategies;

}

function change_rendering_strategies($form, $form_state){

	//$options = get_rendering_strategies_load($form, $form_state);
	return $form['form_attributes']['rendering_strategy'];

}
function change_rendering_strategies_templates(&$form, $form_state){
    //return $form['form_attributes']['form_template'];
	//$options = get_rendering_strategies_load($form, $form_state);
    $form['form_attributes']['template_wrapper']['form_template']['#states'] = array(
       'required' => array(
            ':input[name="rendering_type"]' => array('!value' => 'program-template'),
        ),
    );
    return array(
        '#type' => 'ajax',
        '#commands' => array(
          ajax_command_replace("#rendering_strategy_container", render($form['form_attributes']['rendering_strategy'])),
          ajax_command_replace("#templates_container", render($form['form_attributes']['template_wrapper']['form_template'])),
        )
    );

}


function landingpages_get_form_engine_skins($form, $form_state){

	//$skins = &drupal_static(__FUNCTION__);

    $skins = array('' => '-- Select a Skin --');

	$rendering_strategy = "";
	if ((isset($form_state['values']) && !empty($form_state['values']['rendering_strategy'])) || !empty($form['form_attributes']['rendering_strategy']['#default_value'])) {

		if(!empty($form_state['values']['rendering_strategy'])){
			$rendering_strategy = $form_state['values']['rendering_strategy'];

		}else{
			$rendering_strategy = $form['form_attributes']['rendering_strategy']['#default_value'];
		}
	}

	$request = drupal_http_request(_eddy_form_engine_get_form_domain_for_server_side_calls() . "/TemplateManager/GetThemes?RenderingStrategyName=" . $rendering_strategy . "&callback=jsonCallback");
	$jsonInput = str_replace(');','',str_replace('jsonCallback(','',$request->data));
	$decoded = json_decode($jsonInput, true);

	foreach ($decoded as $key => $value) {
		$skins[$value['Name']] = $value['Name'];
	}

	return $skins;

}

function change_form_skin($form, $form_state){

	//$options = landingpages_get_form_engine_skins($form, $form_state);
	return $form['form_attributes']['form_skin'];

}

/**
 * Submit function for adding or editing a form.
 */

function eddy_forms_engine_add_form_submit($form, &$form_state) {

	$form_engine = $form_state['values'];

	$path = 'admin/structure/eddy_forms_engine/manage/';
	eddy_forms_engine_save($form_engine);

	$form_state['redirect'] = $path . $form_engine['form_name'];

}

function eddy_forms_engine_save($form_engine) {

    $fields = eddy_form_engine_fields($form_engine, 'save');

    try
    {
		$result = TRUE;

		$feid = db_insert('eddy_forms_engine')
		->fields($fields)
		->execute();

		$form_engine['id'] = $feid;

		if ($fields['published'] == 1) {
			$num_updated = db_update('eddy_forms_engine')
			->fields(array('published' => 0,))
			->condition('id', $feid, '<>')
			->execute();

			variable_set('eddy_forms_engine_published_form_id', $feid);
		}

		if($result)
			drupal_set_message(t('Your configuration has been saved.'));
		else
			drupal_set_message(t('There was an issue with your configuration.'));



		cache_clear_all();
	}
	catch (Exception $e)
	{
		drupal_set_message(t('There was an issue with your configuration.'));
		dsm($e);
	}

}

function eddy_form_engine_fields($form_engine, $action){
	/* Set up the array of fields to insert into the database.
     *  Skipping the fields that are unneccessary to save the values for.
     */
	$fields = array();
	$fields['name'] = $form_engine['form_name'];

	if($action == 'save')
		$fields['machine_name'] = $form_engine['machine_name'];

	$fields['description'] = $form_engine['description'];
    $fields['rendering_type'] = $form_engine['rendering_type'];
    $fields['rendering_strategy'] = $form_engine['rendering_strategy'];
    $fields['header_arrows_included'] = $form_engine['header_arrows_included'];

    if($fields['rendering_type'] == 'program-template'){
        $form_engine['form_template'] = 0;
    }

    $fields['form_template'] = $form_engine['form_template'];

	$fields['form_skin'] = $form_engine['form_skin'];
	//$fields['rendering_div'] = $form_engine['rendering_div'];
	$fields['published'] = $form_engine['published'];
	$fields['facts'] = $form_engine['facts'];
	$fields['further_info'] = $form_engine['further_info'];
    $fields['program_template_message'] = $form_engine['program_template_message']['value'];
	$fields['thank_you_title'] = $form_engine['thank_you_title'];
	$fields['thank_you_success_message'] = $form_engine['thank_you_success_message']['value'];
	$fields['thank_you_failed_message'] = $form_engine['thank_you_failed_message']['value'];
	$fields['set_yourself_up'] = $form_engine['set_yourself_up']['value'];
	$fields['tuition_tips'] = $form_engine['tuition_tips']['value'];
	$fields['student_guide'] = $form_engine['student_guide']['value'];
    $fields['form_custom_attributes'] = $form_engine['form_custom_attributes'];

    $start_redirect = $form_engine['workflow_start_redirect'];

    //save '<front>' if using <front> to refer front page.
	if(!empty($start_redirect)){
        if($start_redirect == '<front>'){
            $fields['workflow_start_redirect'] = $start_redirect;
        }else{
            $node_path = explode('/', drupal_get_normal_path($start_redirect));
            $fields['workflow_start_redirect'] = 'node/' . $node_path[1];
        }
	}else{
        $fields['workflow_start_redirect'] = '';
    }

	if(!empty($form_engine['workflow_managedchoice_redirect'])){
		$node_path = explode('/', drupal_get_normal_path($form_engine['workflow_managedchoice_redirect']));
		$fields['workflow_managedchoice_redirect'] = 'node/' . $node_path[1];
	}else{
        $fields['workflow_managedchoice_redirect'] = '';
    }

	if(!empty($form_engine['workflow_thankyou_redirect'])){
		$node_path = explode('/', drupal_get_normal_path($form_engine['workflow_thankyou_redirect']));
		$fields['workflow_thankyou_redirect'] = 'node/' . $node_path[1];
	}else{
        $fields['workflow_thankyou_redirect'] = '';
    }

	if(!empty($form_engine['workflow_nomatch_redirect'])){
		$node_path = explode('/', drupal_get_normal_path($form_engine['workflow_nomatch_redirect']));
		$fields['workflow_nomatch_redirect'] = 'node/' . $node_path[1];
	}else{
        $fields['workflow_nomatch_redirect'] = '';
    }

	return $fields;
}

/**
 * Returns an non-https version of the Form Domain because it causes errors with drupal_http_request()
 */
function _eddy_form_engine_get_form_domain_for_server_side_calls(){

    return str_replace("https://", "http://", variable_get("eddy_forms_engine_service_domain"));

}