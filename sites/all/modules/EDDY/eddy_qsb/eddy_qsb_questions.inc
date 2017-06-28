<?php

/**
 * @file
 * Administrative page callbacks for QSB module.
 */


/**
 * qsb callback; Build the QSB questions editing form.
 */
drupal_add_js(drupal_get_path('module', 'eddy_qsb') .'/js/eddy_qsb_admin.js');

function eddy_questions_edit($form, &$form_state, $type, $qsb) {
	
	$isdegree = $qsb['qsb_type'] == EDDY_QSB_TYPE_DEGREE ? TRUE:FALSE;
	
	$degree_qtype = array(
		'' => t('-- Select a Degree Question Type --'),
		EDDY_QSB_DEGREE_QTYPE_LEVEL => t('Degree ' . EDDY_QSB_DEGREE_QTYPE_LEVEL),
		EDDY_QSB_DEGREE_QTYPE_CAT => t(EDDY_QSB_DEGREE_QTYPE_CAT),
		EDDY_QSB_DEGREE_QTYPE_SUB => t(EDDY_QSB_DEGREE_QTYPE_SUB),		
	);
	//$qq_degree_format = array(

	
	$qq_degree_format = array(
		EDDY_QSB_DEGREE_QTYPE_LEVEL => array(
										0 => array(
											'title' => 'Level',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_LEVEL,
											'qq_field_label' => t('-- Select Degree Level --'),
											),
										1 => array(
											'title' => 'Category',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_CAT,
											'qq_field_label' => t('-- Select a Category --'),
											),
										2 => array(
											'title' => 'Subject',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_SUB,
											'qq_field_label' => t('-- Select a Subject --'),
											),
										),
		EDDY_QSB_DEGREE_QTYPE_CAT => array(
										0 => array(
											'title' => 'Category',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_CAT,
											'qq_field_label' => t('-- Select a Category --'),
											),
										1 => array(
											'title' => 'Subject',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_SUB,
											'qq_field_label' => t('-- Select a Subject --'),
											),
										2 => array(
											'title' => 'Level',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_LEVEL,
											'qq_field_label' => t('-- Select Degree Level --'),
											),		
									),
		EDDY_QSB_DEGREE_QTYPE_SUB => array(
										0 => array(
											'title' => 'Category',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_CAT,
											'qq_field_label' => t('-- Select a Category --'),
											),
										1 => array(
											'title' => 'Subject',
											'qq_type' => EDDY_QSB_DEGREE_QTYPE_SUB,
											'qq_field_label' => t('-- Select a Subject --'),
											),
										),
		);	
	$qq_career_format = array(
		0 => array(
			'title' => EDDY_QSB_CAREER_QTYPE_INDU,
			'qq_type' => EDDY_QSB_CAREER_QTYPE_INDU,
			'qq_field_label' => t('Select ' . EDDY_QSB_CAREER_QTYPE_INDU),
		),
		1 => array(
			'title' => EDDY_QSB_CAREER_QTYPE_OCCU,
			'qq_type' => EDDY_QSB_CAREER_QTYPE_OCCU,
			'qq_field_label' => t('Select ' . EDDY_QSB_CAREER_QTYPE_OCCU),
		),
	);

	$qq_campus_format = array(
		0 => array(
			'title' => EDDY_QSB_CAMPUS_QTYPE_STATE,
			'qq_type' => EDDY_QSB_CAMPUS_QTYPE_STATE,
			'qq_field_label' => t('Select ' . EDDY_QSB_CAMPUS_QTYPE_STATE),
		),
		1 => array(
			'title' => EDDY_QSB_CAMPUS_QTYPE_CITY,
			'qq_type' => EDDY_QSB_CAMPUS_QTYPE_CITY,
			'qq_field_label' => t('Select ' . EDDY_QSB_CAMPUS_QTYPE_CITY),
		),
	);
	
	
	$o_status = array(
		'display' => t('Display'),
		'hide' => t('Hide'),
		'inactive' => t('Inactive'),
	);
	
	$form['questions'] = array(
		'#prefix' => '<h2>' . $qsb['title'] . ' Questions Setup</h2>' . '<div class="qsb-admin qdf-question-container">',
		'#suffix' => '</div>',
	);

	$form['qsb_name'] = array(
		'#type' => 'value',
		'#value' => $qsb['qsb_name'],
	);

	//for adding a Degree Finder
	if($isdegree && $type == 'add' && $qsb['qq_total'] == '3' ){
		
		$form['questions']['qq_first'] = array(
			'#type' => 'select',
			'#title' => t('First Question Setup'),
			'#options' => array(
				'' => t('-- Select the First Question --'),
				EDDY_QSB_DEGREE_QTYPE_LEVEL => t('Degree Level as the first question'),
				EDDY_QSB_DEGREE_QTYPE_CAT => t('Category as the first question'),
			),
			'#default_value' => EDDY_QSB_DEGREE_QTYPE_LEVEL,
			'#required' => TRUE,
			'#ajax' => array(
				'callback' => 'question_sequence_callback',
				'wrapper' => 'qdf_questions_container',
			),
			'#states' => array(
				'visible' => array(
					':input[name="question_level"]' => array('value' => '3'),
					),
			),
			
		);
	}
	
	$form['questions']['question_container'] = array(
		'#prefix' => '<div id="qdf_questions_container">',
		'#suffix' => '</div>',
	);
	//only works for Degree Finder
	if($type == 'add'){
		switch($qsb['qsb_type']){
			case EDDY_QSB_TYPE_DEGREE:
				//initial set level as first question
				if($qsb['qq_total'] == '3')
					$qq_select_type = $qq_degree_format[EDDY_QSB_DEGREE_QTYPE_LEVEL];
				else
					$qq_select_type = $qq_degree_format[EDDY_QSB_DEGREE_QTYPE_SUB];
				break;
			case EDDY_QSB_TYPE_CAREER:
				$qq_select_type = $qq_career_format;
				break;
			case EDDY_QSB_TYPE_CAMPUS:
				$qq_select_type = $qq_campus_format;
				break;
		}
	}
	$num = 0;

	//for initial adding questions, $qqs will be empty array
	$qqs = array();
	//if it's adding questions, then 
	if($type != 'add'){		
		$qqs = qsb_questions_load($qsb['qsb_name']);
	}else{
		//for adding questions, create empty question item
		for($n = 0; $n< $qsb['qq_total']; $n++){
			array_push($qqs, array());	
		}
	}	
	if(!empty($qqs)){
		foreach($qqs as $questions){

			$form['questions']['question_container'][$num] = array(
				'#type' => 'fieldset',
				'#title' => empty($questions['qq_type']) ? $qq_select_type[$num]['title'] : $questions['qq_type'],
				'#collapsible' => FALSE,
				'#tree' => TRUE,	
				);
			$form['questions']['question_container'][$num]['qq_field_type'] = array(
				'#type' => 'value',
				'#value' => 'dropdown',
				);
			$form['questions']['question_container'][$num]['sequence'] = array(
				'#type' => 'value',
				'#value' => $num,
				);
			$form['questions']['question_container'][$num]['qq_type'] = array(
				'#type' => 'value',
				'#value' => empty($questions['qq_type']) ? $qq_select_type[$num]['qq_type'] : $questions['qq_type'],
				);
			$form['questions']['question_container'][$num]['qq_label'] = array(
				'#type' => 'textfield',
				'#title' => t('Title'),
				'#size' => 40,
				'#default_value' => empty($questions['qq_label']) ? '' : $questions['qq_label'],
				'#maxlength' => 128,
				'#prefix' => '<div class="clearfix"><div class="inline">',
				'#suffix' => '</div>',

				);	
			$form['questions']['question_container'][$num]['qq_field_label'] = array(
				'#type' => 'textfield',
				'#title' => t('Dropdown Default Value'),
				'#size' => 40,
				'#default_value' => empty($questions['qq_field_label']) ? '' : $questions['qq_field_label'],
				'#maxlength' => 128,
				'#required' => TRUE,
				'#prefix' => '<div class="inline">',
				'#suffix' => '</div></div>',
				);
			if($num != 0){
				$form['questions']['question_container'][$num]['o_status'] = array(		
					'#type' => 'radios',
					'#title' => t('Status on first loading'),
					'#options' => $o_status,
					'#default_value' => empty($questions['o_status']) ? 'display' : $questions['o_status'],
					);
			}else{
				$form['questions']['question_container'][$num]['o_status'] = array(
					'#type' => 'value',
					'#value' => 'display',
					);
			}	

			$num++;	

		}


		if(!empty($form_state['values']['qq_first'])){
			if($form_state['values']['qq_first'] == EDDY_QSB_DEGREE_QTYPE_LEVEL){
				$qq_select_type = $qq_degree_format[EDDY_QSB_DEGREE_QTYPE_LEVEL];
			}else{
				$qq_select_type = $qq_degree_format[EDDY_QSB_DEGREE_QTYPE_CAT];
			}
            
	        for($num = 0; $num<$qsb['qq_total']; $num++){
		        //have to unset 'input' to allow accept new #value
		        unset($form_state['input'][$num]['qq_field_label']);
		        //change the first and second questions title, qq_type, and dropdown default value
		        $form['questions']['question_container'][$num]['#title'] = $qq_select_type[$num]['title'];
		        $form['questions']['question_container'][$num]['qq_type']['#value'] = $qq_select_type[$num]['qq_type'];
		        $form['questions']['question_container'][$num]['qq_field_label']['#default_value'] = $qq_select_type[$num]['qq_field_label'];
	        }
            
        }
		$form['prechk_filter'] = array(
            '#type' =>'checkbox', 
            '#title' => t('Enable pre-select by node filters'),
            '#default_value' => empty($qsb['prechk_filter']) ? 0 : $qsb['prechk_filter'],
            '#description' => t('By checking this, dropdown item will be pre-selected according to current node filters.'),
        );

		$form['submit_text'] = array(
			'#type' => 'textfield',
			'#title' => t('Submit Button Text'),
			'#size' => 10,
			'#default_value' => empty($qsb['submit_text']) ? 'Find Now' : $qsb['submit_text'],
			'#required' => TRUE,
			'#maxlength' =>32,
		);
		$form['actions'] = array('#type' => 'actions');
		$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Save'),
		);
		$form['actions']['continue'] = array(
			'#type' => 'submit',
			'#value' => t('Save & Continue Setup Style'),	
			'#access' => $type == 'add',	
			'#submit' => array('eddy_questions_edit_continue'),
			);
		$form['actions']['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete'),
			'#access' => $type == 'edit',
			'#submit' => array('eddy_questions_delete_submit_redirect'),
		);
	}else{
		drupal_set_message(t('To edit questions, please go back Quick Search Builder to create questions first.'), 'warning');
		$form['actions'] = array('#type' => 'actions');
		$form['actions']['goback'] = array(
			'#type' => 'submit',
			'#value' => t('Create Questions'),	
			'#submit' => array('eddy_questions_add_goback'),
			);
	}
	return $form;
}


/**
 * Process QSB questions add/edit form submissions.
 */
 
function eddy_questions_edit_submit($form, &$form_state) {
	$questions = $form_state['values'];
	$path = 'admin/structure/qsb/manage';

	qsb_question_save($questions);
	$form_state['redirect'] = $path . '/' . $questions['qsb_name'];
}

//Degree's questions change sequence callback
function question_sequence_callback($form, $form_state){	
	return $form['questions']['question_container'];
}


/**
 * Submit function for the 'Delete' button on the QSB question editing form.
 */
function eddy_questions_delete_submit_redirect($form, &$form_state) {
	$form_state['redirect'] = 'admin/structure/qsb/manage/' . $form_state['values']['qsb_name'] . '/questions/delete';
}


/**
 * qsb callback; check access and get a confirm form for deletion of QSB question.
 */
 
function eddy_questions_delete_page($qsb) {
	return drupal_get_form('eddy_questions_delete_page_confirm', $qsb);
}


/**
 * Build a confirm form for deletion of QSB question.
 */
 
function eddy_questions_delete_page_confirm($form, &$form_state, $qsb) {
	try{
        $form['#qsb_questions'] = $qsb;
	    $caption = '';
	    $num_questions = db_query("SELECT COUNT(*) FROM {eddy_qsb_questions} WHERE qsb_name = :qsb", array(':qsb' => $qsb['qsb_name']))->fetchField();
	    if ($num_questions) {
		    $caption .= '<p>' . format_plural($num_questions, '<strong>Warning:</strong> There is currently 1 QSB question relates %title. It will be deleted.', '<strong>Warning:</strong> There are currently @count QSB questions relate in %title. They will be deleted.', array('%title' => $qsb['title'])) . '</p>';
	    }
	    $caption .= '<p>' . t('This action cannot be undone.') . '</p>';
	    return confirm_form($form, t('Are you sure you want to delete the QSB %title questions?', array('%title' => $qsb['title'])), 'admin/structure/qsb/manage/' . $qsb['qsb_name'] . '/questions', $caption, t('Delete'));
     }
    catch (Exception $e) {
		dpm($e);
	}
}


/**
 * Delete all questions in the QSB.
 */

function eddy_questions_delete_page_confirm_submit($form, &$form_state) {
	$qsb = $form['#qsb_questions'];
	$form_state['redirect'] = 'admin/structure/qsb';

	// Delete the custom qsb and all its questions.
	qsb_questions_delete($qsb);

}

function eddy_questions_edit_continue($form, &$form_state){
	
	$questions = $form_state['values'];	
	$path = 'admin/structure/qsb/manage/';
	qsb_question_save($questions);
	
	$form_state['redirect'] = $path . $questions['qsb_name'] . '/style';
}