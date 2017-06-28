<?php

/**
 * @file
 * Administrative page callbacks for qsb module.
 */


/**
 * qsb callback; Build the QSB style editing form.
 */
drupal_add_js(drupal_get_path('module', 'eddy_qsb') .'/js/eddy_qsb_admin.js');

function qsb_style_setup($form, &$form_state, $type, $qsb) {

	$form['qsb_name'] = array(
		'#type' => 'value',
		'#value' => $qsb['qsb_name'],
		);
	if(qsb_questions_load($qsb['qsb_name']) != false){
		//select style section
		$form['qsb_name'] = array(
			'#type' => 'value',
			'#value' => $qsb['qsb_name'],
			);

		$form['qsb_style'] = array(
			'#prefix' => '<div class="clearfix" ><div id="qdf_style_container" class="qsb-admin qdf_style_container inline" >',
			'#suffix' => '</div>',
			);		
        

        //$form['email_admin_created'] = array(
        //    '#type' => 'fieldset',
        //    '#title' => t('Form Container Setting'),
        //    '#collapsible' => TRUE,
        //    '#collapsed' => (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL) != USER_REGISTER_ADMINISTRATORS_ONLY),
        //    '#group' => 'email',
        //  );
        $form['qsb_style']['background_setting'] = array(
            '#type' => 'fieldset',
            '#title' => t('Background Settings'),
			);
        $form['qsb_style']['background_setting']['color'] = array(
            '#type' => 'textfield',
            '#title' => t('Background Color:'),    	
            '#default_value' => empty($qsb['style_color']) ? '': $qsb['style_color'],
            '#description'=> t('Please put hex color at here, etc. #FFFFFF.'),
        );
        $form['qsb_style']['background_setting']['image'] = array(
                
                    '#type' => 'managed_file',
                    '#title' => t('Background Image:'),
                    '#progress_message' => t('Please wait...'),
                    '#progress_indicator' => 'bar',
                    '#upload_validators' => array(
                        'file_validate_extensions' => array('gif png jpg jpeg'),
                        'file_validate_size' => array(1 * 1024 * 1024),
                    ),
                    '#description' => t('Click "Browse..." to select an image to upload. Allowed image format: *.gif, *.png, *.jpg, *.jpeg. <b>No space is allowed in file name.</b>'),
                    '#default_value' => $qsb['image_fid']? $qsb['image_fid']:0,
                    '#upload_location' => EDDY_QSB_IMAGE_PATH,//'public://backgroundimage/', //
                    '#theme' => 'qsb_thumb_upload',
                );
        $form['qsb_style']['background_setting']['image_position'] = array(
            '#type' => 'radios',
			'#title' => t('Background Image position:'),
			'#options' => array(
				'image_left' => 'Left',			
                'image_center' => 'Center',			
				'image_right' => 'Right',
					),
		    '#default_value' => empty($qsb['image_alignment']) ? '': $qsb['image_alignment'],
            '#states' => array(
					'invisible' => array(
						':input[name="image"]' => array('value' => '0'),
						),
					),		
            '#group' => 'qsb_form',
        );
        $form['qsb_style']['form_setting'] = array(
            '#type' => 'fieldset',
            '#title' => t('Form Settings'),
        );
        $form['qsb_style']['form_setting']['form_width'] = array(
           '#type' => 'textfield',
           '#title' => t('Form Width:'),    	
           '#default_value' => empty($qsb['form_width']) ? '': $qsb['form_width'],
           '#description'=> t('Please put % or px, etc. "50%", "200px". Leave it blank for "auto"'),
       );
        $form['qsb_style']['form_setting']['form_height'] = array(
           '#type' => 'textfield',
           '#title' => t('Form Height:'),    	
           '#default_value' => empty($qsb['form_height']) ? '': $qsb['form_height'],
           '#description'=> t('Please put px for form height, etc. "100px". Leave it blank for "auto"'),
       );
        $form['qsb_style']['form_setting']['form_position'] = array(
                    '#type' => 'radios',
                    '#title' => t('Form Position:'),
                    '#options' => array(
                        'form-left' => 'Left',			
                        'form-center' => 'Center',
                        'form-right' => 'Right',
                            ),
                    '#default_value' => empty($qsb['form_alignment']) ? '': $qsb['form_alignment'],
	
         );
        $form['qsb_style']['form_setting']['form_padding'] = array(
           '#type' => 'textfield',
           '#title' => t('Form Padding:'),    	
           '#default_value' => empty($qsb['form_padding']) ? '': $qsb['form_padding'],
           '#description'=> t('This is the setting for "padding" style. Example setting is "10px 5px 0px 8px", which means "padding-top:10px; padding-right:5px; padding-bottom:0px; padding-left:8px;".'),
       );
        $form['qsb_style']['question_setting'] = array(
            '#type' => 'fieldset',
            '#title' => t('Other Settings'),
        );
		$form['qsb_style']['question_setting']['question_align'] = array(
			'#type' => 'radios',
			'#title' => t('QSB questions show in:'),
			'#options' => array(
				'question-block' => 'Seperate Line',			
				'question-inline' => 'Same Line',
					),
				'#default_value' => empty($qsb['question_alignment']) ? 'question-block': $qsb['question_alignment'],
			);			
		$form['qsb_style']['question_setting']['title_align'] = array(
			'#type' => 'radios',
			'#title' => t('QSB title align to:'),
			'#options' => array(
				'title-left' => 'Left',			
				'title-center' => 'Center',
				'title-right' => 'Right',
					),
				'#default_value' => empty($qsb['title_alignment']) ? 'title-left': $qsb['title_alignment'],
			);
        $form['qsb_style']['question_setting']['button_skin'] = array(
            '#type' => 'select',
            '#title' => t('QSB Button Skin:'),
            '#options' => array(
				'' => '--Select a Skin Color--',
                'black' => 'Black',
                'blue' => 'Blue',
                'burn' => 'Burn',
                'gray' => 'Gray',
                'green' => 'Green',	
                'navy' => 'Navy',
                'orange' => 'Orange',
                'red' => 'Red',
                'rosy' => 'Rosy',
                'white' => 'White',          
					),
            '#default_value' => empty($qsb['button_skin']) ? '': $qsb['button_skin'],
            );
		$form['qsb_style']['question_setting']['button_align'] = array(
			'#type' => 'radios',
			'#title' => t('QSB button align to:'),
			'#options' => array(
				'button-left' => 'Left',			
				'button-center' => 'Center',
				'button-right' => 'Right',
					),
				'#default_value' => empty($qsb['button_alignment']) ? 'button-left': $qsb['button_alignment'],
			);
        $form['qsb_style_preview'] = array(
        '#prefix' => '<div id="qdf_style_preview_container" class="qsb-admin qdf_style_preview_container inline" ><p><strong>The form you see at here is not exactly the same as on page. The width of QDF relies on the width of block or region on the page. And you are not able to see the dropdown data at here.</strong></p>',
        '#suffix' => '</div></div>',
        '#markup' => theme('qsb_style_preview', array('qsb' => $qsb, 'q_question' => qsb_questions_load($qsb['qsb_name']))),
        );
		
		$form['actions'] = array('#type' => 'actions');
		$form['actions']['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Save'),
			'#attributes' => array('class'=> array('block')),

			);

	}else{
		drupal_set_message(t('To setup this question style, please add QSB questions first.'), 'warning');
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
 * Process QSB style form submissions.
 */

function qsb_style_setup_submit($form, &$form_state) {

	$qsb = $form_state['values'];
	$path = 'admin/structure/qsb/manage';
    
	qsb_style_save($qsb);
	$form_state['redirect'] = $path . '/' . $qsb['qsb_name'];
    
}
