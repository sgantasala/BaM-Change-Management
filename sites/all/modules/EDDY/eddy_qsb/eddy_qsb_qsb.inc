<?php

/**
 * @file
 * Administrative page callbacks for QSB module.
 */


drupal_add_js(drupal_get_path('module', 'eddy_qsb') .'/js/eddy_qsb_admin.js');

// QSB callback which shows an overview page of all the QSBs and their descriptions.
function qsb_overview_page() {
	$result = qsb_load_all(); 
	$header = array(t('Title'), t('Type'), array('data' => t('Operations'), 'colspan' => '3'));
	$rows = array();
	foreach ($result as $qsb) {
		$qq = qsb_questions_load($qsb['qsb_name']);
		$row = array(theme('qsb_admin_overview', array('title' => $qsb['title'], 'name' => $qsb['qsb_name'], 'description' => $qsb['description'])));
		$row[] = array('data' => t(ucwords($qsb['qsb_type'])));
		$row[] = array('data' => l(t('config QSB'), 'admin/structure/qsb/manage/' . $qsb['qsb_name'] . '/edit'));
		if(!empty($qq)){
			$row[] = array('data' => l(t('edit Questions'), 'admin/structure/qsb/manage/' . $qsb['qsb_name'] . '/questions/edit'));
			$row[] = array('data' => l(t('setup & preview style'), 'admin/structure/qsb/manage/' . $qsb['qsb_name'] . '/style'));
		}else{
			$row[] = array('data' => l(t('create Questions'), 'admin/structure/qsb/manage/' . $qsb['qsb_name'] . '/questions/add'));
			$row[] = array('data' => '');
		}
		$rows[] = $row;
	}
	return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Returns HTML for a qsb title and description for the QSB overview page.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: The QSB's title.
 *   - description: The QSB's description.
 *
 * @ingroup themeable
 */
function theme_qsb_admin_overview($variables) {
	$output = check_plain($variables['title']);
	$output .= '<div class="description">' . filter_xss_admin($variables['description']) . '</div>';

	return $output;
}


// QSB callback; Build the form that handles the adding or editing of a QSB.
function eddy_qsb_edit($form, &$form_state, $type, $qsb = array()) {

	$qsb += array(
		'qsb_name' => '',
		'old_name' => !empty($qsb['qsb_name']) ? $qsb['qsb_name'] : '',
		'title' => '',
		'qsb_type' => '',
		'qq_total' => '',
		'style_color' => '',
		'title_alignment' => '',
		'button_alignment' => '',
		'submit_type' => '',
		'submit_url' => '',	
		'description' => '',
	);
	// Allow qsb_edit_qsb_submit() and other form submit handlers to determine
	// whether the QSB already exists.
	$form['#insert'] = empty($qsb['old_name']);
	$form['old_name'] = array(
		'#type' => 'value',
		'#value' => $qsb['old_name'],
	);

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Quick Search Name'),
		'#default_value' => $qsb['title'],
		'#maxlength' => 128,
		'#description' => t('The maximum length of title is 128'),
		'#required' => TRUE,
		// '#rules' => array('qsb_name_exists'),

	);
	$form['qsb_name'] = array(
		'#type' => 'machine_name',
		'#title' => t('QSB machine name'),
		'#default_value' => $qsb['qsb_name'],
		'#maxlength' => 60,
		'#description' => t('A unique name to construct the URL for the QSB. It must only contain lowercase letters, numbers and hyphens.'),
		'#machine_name' => array(
			'exists' => 'check_qsb_name_exists',
			'source' => array('title'),
			'label' => t('Machine name'),
			'replace_pattern' => '[^a-z0-9-]+',
			'replace' => '-',
		),
		// A qsb's machine name cannot be changed.
		'#disabled' => !empty($qsb['old_name']),
	);    
	if($type == 'add'){
		$form['qsb_type'] = array(
			'#type' => 'radios',
			'#title' => t('QSB Type'),
			'#options' => array(
					EDDY_QSB_TYPE_DEGREE => t(EDDY_QSB_TYPE_DEGREE . ' Finder'),
					EDDY_QSB_TYPE_CAMPUS => t(EDDY_QSB_TYPE_CAMPUS . ' Search'),
					EDDY_QSB_TYPE_CAREER => t(EDDY_QSB_TYPE_CAREER . ' Search'),
					),
			'#disabled_values' => array(EDDY_QSB_TYPE_CAMPUS, EDDY_QSB_TYPE_CAREER),
			'#default_value' => empty($qsb['qsb_type']) ? 'Degree' : $qsb['qsb_type'],
			'#required' => TRUE,
			// '#ajax' => array(
				// //'callback' => 'qsb_type_callback',
				// 'wrapper' => 'degree_type_div',
				// ),
			'#prefix' => '<div class="qdf-form-item main-item">',
			'#suffix' => '</div>',
		);
		$form['question_level'] = array(
			'#type' => 'select',
			'#title' => t('Question Level'),
			'#options' => array(
				'' => t('-- Select a Degree Question Levels --'),
				'2' => t('Two Levels:Category and Subject'),
				'3' => t('Three Levels:Category, Subject, and Degree Level'),
			),
			'#default_value' => '',
			'#required' => TRUE,
			'#ajax' => array(
				'callback' => 'question_level_callback',
				'wrapper' => 'degree_type_div',
			),
		);

	}else{
		$form['qsb_type'] = array(
			'#type' => 'value',
			'#value' => empty($qsb['qsb_type']) ? 'Degree' : $qsb['qsb_type'],			
			);	
		$form['qsb_type_label'] = array(
			'#markup' => '<strong>QSB Type:</strong> ' . $qsb['qsb_type'],
			);
	}	

	$form['degree_type_div'] = array(
		'#prefix' => '<div id="degree_type_div">',
		'#suffix' => '</div>',
		);
	$form['degree_type_div']['qq_total'] = array(
		'#type' => 'hidden',
		'#default_value' => empty($qsb['qq_total']) ? '3' : $qsb['qq_total'],
		);
	
	// This is only for Degree QSB
	if((($type != 'add') && $qsb['qsb_type'] == EDDY_QSB_TYPE_DEGREE) || ($type == 'add')){		

        $form['degree_type_div']['submit_type'] = array(
            '#type' => 'radios',
            '#title' => t('Submit this Quick Search to:'),            
            '#options' => array(
                    'qdf-listing' => t('Program Listing'),
                    'qdf-form' => t("Form/Wizard Page"),  
                    ),
                '#default_value' => (empty($qsb['submit_type']) ? 'qdf-listing' : $qsb['submit_type']),
                '#required' => TRUE,
                '#prefix' => '<div class="qdf-form-item main-item">',
                '#suffix' => '</div>',
                );

		$form['degree_type_div']['submit_url'] = array(
			'#type' => 'textfield',
			'#title' => t('Submit to URL:'),
			'#default_value' => empty($qsb['submit_url']) ? variable_get('eddy_core_form_url') : $qsb['submit_url'],
			'#maxlength' => 255,
			'#size' => 100,
			'#description' =>  t('Submitting this QSB will go to this specific URL. Note: Default value comes from <b>eddy_core_form_url</b> variable configuration.'),
			'#prefix' => '<div class="qdf-form-item sub-item">',
			'#suffix' => '</div>',
			);
	}
	$form['description'] = array(
		'#type' => 'textarea',
		'#title' => t('Description'),
		'#default_value' => $qsb['description'],
	);
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
	$form['actions']['continue'] = array(
		'#type' => 'submit',
		'#value' => t('Save & Create Questions'),
		'#access' => $type == 'add',
		'#submit' => array('eddy_qsb_edit_continue'),
	);
	// custom qsbs may be deleted.
	$form['actions']['delete'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#access' => $type == 'edit',
		'#submit' => array('eddy_qsb_delete_submit_redirect'),
	);

	return $form;
}

// QSB type callback
// function qsb_type_callback($form, $form_state){	

	// if(!empty($form_state['values']['qsb_type']) && ($form_state['values']['qsb_type'] == EDDY_QSB_TYPE_DEGREE)){		

		// unset($form_state['input']['qq_total']);
		// $form['degree_type_div']['qq_total']['#value'] = '3';	
		
	// }else{
		
		// $form['degree_type_div']['submit_type'] = array();
		// $form['degree_type_div']['submit_url'] = array();
		// unset($form_state['input']['qq_total']);
		// $form['degree_type_div']['qq_total']['#value'] = '2';	
		
	// }
	// //dsm($form['degree_type_div']);
	// return $form['degree_type_div'];
// }

// QSB Question level callback
function question_level_callback($form, $form_state){	

	if(!empty($form_state['values']['question_level']) && ($form_state['values']['question_level'])){		

		unset($form_state['input']['qq_total']);
		$form['degree_type_div']['qq_total']['#value'] = $form_state['values']['question_level'];	
		
	}
	//dsm($form['degree_type_div']);
	return $form['degree_type_div'];
}

/**
 * Submit function for the 'Delete' button on the QSB editing form.
 */
function eddy_qsb_delete_submit_redirect($form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/qsb/manage/' . $form_state['values']['qsb_name'] . '/delete';
}


/**
 * qsb callback; check access and get a confirm form for deletion of a custom qsb.
 */
 
function eddy_qsb_delete_page($qsb) {
	return drupal_get_form('eddy_qsb_delete_page_confirm', $qsb);
}

/**
 * Build a confirm form for deletion of a custom qsb.
 */
 
function eddy_qsb_delete_page_confirm($form, &$form_state, $qsb) {
    try{
	    $form['#qsb'] = $qsb;
	    $caption = '';
	    $num_questions = db_query("SELECT COUNT(*) FROM {eddy_qsb_questions} WHERE qsb_name = :qsb", array(':qsb' => $qsb['qsb_name']))->fetchField();
	
	    if ($num_questions) {
		    $caption .= '<p>' . format_plural($num_questions, '<strong>Warning:</strong> There is currently 1 QSB question relates %title. It will be deleted.', '<strong>Warning:</strong> There are currently @count QSB questions relate in %title. They will be deleted.', array('%title' => $qsb['title'])) . '</p>';
	    }
	
	    $caption .= '<p>' . t('This action cannot be undone.') . '</p>';
	    return confirm_form($form, t('Are you sure you want to delete the custom QSB %title?', array('%title' => $qsb['title'])), 'admin/structure/qsb/manage/' . $qsb['qsb_name'], $caption, t('Delete'));
    }
    catch (Exception $e) {
		dpm($e);
	}
}

/**
 * Delete a QSB and all questions in it.
 */
 
function eddy_qsb_delete_page_confirm_submit($form, &$form_state) {
	$qsb = $form['#qsb'];
	$form_state['redirect'] = 'admin/structure/qsb';
	
	// Delete the custom qsb and all its questions.
	qsb_delete($qsb);
}


//Look into eddy_qsb to check if the qsb name already exists 
function check_qsb_name_exists($value) {
    
    try{
	    // 'qsb-' is added to the qsb name to avoid qsb-space conflicts.	
	    $value = 'qsb-' . $value;
	    $name_exists = db_query_range('SELECT 1 FROM {eddy_qsb} WHERE qsb_name = :qsb', 0, 1, array(':qsb' => $value))->fetchField();

	    return $name_exists;
    }
    catch (Exception $e) {
		dpm($e);
	}
}

/**
 * Submit function for adding or editing a QSB.
 */
function eddy_qsb_edit_submit($form, &$form_state) {
	$qsb = $form_state['values'];  
	$path = 'admin/structure/qsb/manage/';
	
	if ($form['#insert']) {
		// Prefix 'qsb-' to the qsb name to help avoid name-space conflicts.
		$qsb['qsb_name'] = 'qsb-' . $qsb['qsb_name'];
		
		
	}
	/*if(!check_qsb_name_exists($qsb['qsb_name'])){
		drupal_set_message(t('This title has been used by another QSB, please change your title.'), 'error');
		return false;
	}*/
	qsb_save($qsb);
	$form_state['redirect'] = $path . $qsb['qsb_name'];
  
}

function eddy_qsb_edit_continue($form, &$form_state){
	$qsb = $form_state['values'];
	$path = 'admin/structure/qsb/manage/';
	$qsb['qsb_name'] = 'qsb-' . $qsb['qsb_name'];
	
	qsb_save($qsb);
	$form_state['redirect'] = $path . $qsb['qsb_name'] . '/questions/add';
}
