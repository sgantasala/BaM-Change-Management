<?php

/**
 * Callback function to edit review
 */
function eddy_reviews_add($form, &$form_state, $btype = "program", $associate_id) {
    
    drupal_set_title('Your Review');
    $form['review'] = array(
        '#prefix' => '<div id="eddy_reviews_container">',
		'#suffix' => '</div>',
    );
    $form['review']['btype'] = array(
      '#type' => 'hidden',
      '#value' => $btype,
    );
     $form['review']['associate_id'] = array(
       '#type' => 'hidden',
       '#value' => $associate_id,
     );

     global $base_url;
     
     if(strpos($base_url . '/'. request_path(), 'ajax') === false){
         //not upload image
         $form['review']['prev_page'] = array(
           '#type' => 'hidden',
           '#value' => $_SERVER['HTTP_REFERER'],
         );
         setcookie('prev_page', $_SERVER['HTTP_REFERER'], time()+3600, "/");
     }else{
         //click upload image send a new request to form
         $form['review']['prev_page'] = array(
           '#type' => 'hidden',
           '#value' => $_COOKIE['prev_page'],
         );        
     }
     
     $form['review']['customer_name'] = array(
          '#title' => t('Name'),
          '#type' => 'textfield',
          '#default_value' => '',
          '#required' => TRUE,
        );
     $form['review']['customer_email'] = array(
          '#title' => t('Email'),
          '#description' => t('A valid email address may be required to verify your reviews.'),
          '#type' => 'textfield',
          '#default_value' => '',
          '#required' => TRUE,
        );
    $form['review']['title'] = array(
      '#title' => t('Review Title'),
      '#type' => 'textfield',
      '#default_value' => '',
      '#required' => TRUE,
    );
    $form['review']['description'] = array(
      '#title' => t('Review Text'),
      '#type' => 'textarea',
      '#maxlength' => 3000,
      '#default_value' => '',
      '#required' => TRUE,
      '#description' => t('Max limit of 3,000 characters.'),
    );
    
    $form['review']['rating'] = array(
        '#type' => 'radios',
        '#title' => t('Rating'),
        '#options' => array(
                '1' => ' ',
                '2' => ' ',
                '3' => ' ',
                '4' => ' ',
                '5' => ' ',
                ),
        '#required' => TRUE,
        '#prefix' => '<div class="review-rating">',
        '#suffix' => '</div>',
    );    

    $form['review']['image'] = array(                
        '#type' => 'managed_file',
        '#title' => t('Attach Image:'),
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#upload_validators' => array(
            'file_validate_extensions' => array('gif png jpg jpeg'),
            'file_validate_size' => array(1 * 1024 * 1024),
        ),
        '#description' => t('Click "Choose File" to select an image to upload. Allowed image format: *.gif, *.png, *.jpg, *.jpeg. <b>No space is allowed in file name.</b>'),
        '#default_value' => 0,
        '#upload_location' => EDDY_REVIEW_IMAGE_PATH,//'public://reviews/', //
        '#theme' => 'eddy_reviews_preview_upload',
    );

    $form['review']['recommended'] = array(
       '#type' => 'radios',
       '#title' => t('Would you recommend this program to a friend?'),
       '#options' => array(
               '1' => t('Yes'),
               '0' => t('No'),
               ),
       '#default_value' => '',
       '#required' => TRUE,
       '#prefix' => '<div class="review-recommended">',
       '#suffix' => '</div>',
   );    
    $form['#validate'][] = 'eddy_reviews_validate';
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
         '#submit' => array('eddy_review_edit_submit'),
    );

    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
         '#submit' => array('eddy_review_edit_cancel'),
    );

    return $form;

}

/**
 * Callback function to edit review
 */
function eddy_reviews_edit($form, &$form_state, $rid = '0') {
    
    $reviews = entity_load('eddy_reviews', array($rid));
    $review = $reviews[$rid];
    drupal_set_title($review->title);
    $form['review'] = array(
        '#prefix' => '<div id="eddy_reviews_container">',
        '#suffix' => '</div>',
    );
    $form['review']['rid'] = array(
        '#type' => 'hidden',
        '#value' => $review->rid,
    );
    $form['review']['customer_name'] = array(
        '#title' => t('Name'),
        '#type' => 'textfield',
        '#default_value' => isset($review->customer_name) ? $review->customer_name : '',
        '#required' => TRUE,
    );
    $form['review']['customer_email'] = array(
        '#title' => t('Email'),
        '#description' => t('A valid email address may be required to verify your reviews.'),
        '#type' => 'textfield',
        '#default_value' => isset($review->customer_email) ? $review->customer_email : '',
        '#required' => TRUE,
    );
     $form['review']['title'] = array(
      '#title' => t('Review Title'),
      '#type' => 'textfield',
      '#default_value' => isset($review->title) ? $review->title : '',
      '#required' => TRUE,
    );
    $form['review']['description'] = array(
      '#title' => t('Review'),
      '#type' => 'textarea',
      '#default_value' => isset($review->description) ? $review->description : '',
      '#required' => TRUE,
      '#maxlength' => 3000,
      '#description' => t('Max limit of 3,000 characters.'),
    );
    	
    $form['review']['rating'] = array(
        '#type' => 'radios',
        '#title' => t('Rating'),
        '#options' => array(
                '1' => ' ',
                '2' => ' ',
                '3' => ' ',
                '4' => ' ',
                '5' => ' ',
                ),
        '#default_value' => isset($review->rating) ? $review->rating : '',
        '#required' => TRUE,
        '#prefix' => '<div class="review-rating">',
        '#suffix' => '</div>',
    );    

    $form['review']['image'] = array(                
        '#type' => 'managed_file',
        '#title' => t('Attach Image:'),
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#upload_validators' => array(
            'file_validate_extensions' => array('gif png jpg jpeg'),
            'file_validate_size' => array(1 * 1024 * 1024),
        ),
        '#description' => t('Click "Choose File" to select an image to upload. Allowed image format: *.gif, *.png, *.jpg, *.jpeg. <b>No space is allowed in file name.</b>'),
        '#default_value' => (isset($review->image_fid) && $review->image_fid)? $review->image_fid:0,
        '#upload_location' => EDDY_REVIEW_IMAGE_PATH,//'public://reviews/', //
        '#theme' => 'eddy_review_preview_upload',
    );
    $form['review']['recommended'] = array(
       '#type' => 'radios',
       '#title' => t('Do you recommend this product?'),
       '#options' => array(
               '1' => t('Yes'),
               '0' => t('No'),
               ),
       '#default_value' => isset($review->recommended) ? $review->recommended : '',
       '#required' => TRUE,
       '#prefix' => '<div class="review-recommended">',
       '#suffix' => '</div>',
   );    
    $form['#validate'][] = 'eddy_reviews_validate';
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
         '#submit' => array('eddy_review_edit_submit'),
    );

    //display approve button when it's pending
    $form['actions']['approve'] = array(
        '#type' => 'submit',
        '#value' => t('Save & Approve'),
        '#access' => (isset($review->status) && $review->status == '0'), //pending
         '#submit' => array('eddy_review_edit_submit'),
    );    

    //display publish button when it's approved
    $form['actions']['publish'] = array(
        '#type' => 'submit',
        '#value' => t('Save & Publish'),
        '#access' => (isset($review->status) && $review->status == '1'), //approved
         '#submit' => array('eddy_review_edit_submit'),
    );
    $form['actions']['cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),
         '#submit' => array('eddy_review_edit_cancel'),
    );
    $form['actions']['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
         '#submit' => array('eddy_review_edit_submit'),
    );

    return $form;

}


/**
 * Process review edit form submissions.
 */
function eddy_review_edit_submit($form, &$form_state) {

    $review = $form_state['values'];

    $button = $form_state['clicked_button']['#value'];
    $op = '';
    switch(strtolower($button)){
        case "save & approve":
            eddy_reviews_save($review);
            $op = 'approve';
            break;
        case "delete":
            $op = 'delete';
            break;
        case "save & publish":
            eddy_reviews_save($review);
            $op = 'publish';
            break;
        case "save":
            eddy_reviews_save($review);
            break;
    }

    if(!array_key_exists('btype', $review)){//edit update
        eddy_reviews_status_change($review['rid'], $op, false);
        
    }
    if(isset($review['rid'])){
        drupal_set_message(t('Review changes have been saved.'));
    }else{
        drupal_set_message(t('Thank you for submitting a program review to StudyAbroad.com. Your submission is currently under review and should be visible on the site within 3-5 business days. If you have any questions please contact info@studyabroad.com.'));
    }
    
//    cache_clear_all();

    
    if(array_key_exists('prev_page', $review)){//if it's create then go back to program/institution detail page
        $form_state['redirect'] = $review['prev_page'];
    }else{
        $form_state['redirect'] = EDDY_REVIEW_ADMIN_PATH;//if it's edit then go back to review admin page
    }
    
}


/**
 * Process review edit form save.
 */
function eddy_reviews_save($review) {

    $fields = array();
    $fields['title'] = $review['title'];
    $fields['description'] = $review['description'];
    $fields['rating'] = $review['rating'];
    $fields['image_fid'] = $review['image'];
    $fields['recommended'] = $review['recommended'];
    $fields['customer_name'] = $review['customer_name'];
    $fields['customer_email'] = $review['customer_email'];    

    if(array_key_exists('btype', $review)){// create review
        //save associate base info before insert review
        $bid = save_associate_info($review['btype'], $review['associate_id']);
        //add new review
        $fields['bid'] = $bid;
        $fields['created'] = REQUEST_TIME;

        $rid = db_insert('eddy_reviews') 
        ->fields($fields)
        ->execute();   
        
        //send notice email
        if(variable_get('eddy_reviews_notice_email') != ''){
            $module = 'eddy_reviews';
            $key = 'eddy_reviews_' . $rid;
            $language = language_default();            
            $params = array(
              '@associate' => get_associate_name($review['btype'], $review['associate_id']),
              '@url' => get_associate_link($review['btype'], $review['associate_id']), //url('node/' . $node->nid, array('absolute' => TRUE)),
              '@review_url' => url('admin/reviews', array('absolute' => TRUE)),
              '@title' => $review['title'],
              //'@associate_type' => $review['btype'],
              //'@associate_id' => $review['associate_id'],
            );
            drupal_mail($module, $key, variable_get('eddy_reviews_notice_email'), $language, $params);
        }

    }else{//update review
        global $user;

        $rid = $review['rid'];
        $fields['updated'] = REQUEST_TIME;
        $fields['updated_uid'] = $user->uid;
        db_update('eddy_reviews')
            ->fields($fields)
            ->condition('rid', $rid)
            ->execute();

        update_avg_rating($rid);
    }

    $query = db_select('file_managed', 'f')
     -> fields('f', array('fid'))
     -> condition('fid', $review['image'], '=')
     -> execute();

    $fid = $query->fetchField();

    //Record that the module (in this example, user module) is using the file.
    if(!empty($fid)){
        // Load the file via file.fid.
        $file = file_load($review['image']);
        // Change status to permanent.
        $file->status = FILE_STATUS_PERMANENT;
        // Save.
        file_save($file);

        file_usage_add($file, 'eddy_review', 'eddy_review', $rid);   
    }


    

}
/**
 * Process review edit cancel form submissions.
 */
function eddy_review_edit_cancel($form, &$form_state) {

    //delete file has been uploaded but not been saved with review
    if($form_state['values']['image'] != '0'){
        $file = file_load($form_state['values']['image']);
        file_delete($file);
    }
    
    $form_state['redirect'] = EDDY_REVIEW_ADMIN_PATH;
    
}

function eddy_reviews_validate($form, &$form_state){

    $form_values = $form_state['values'];
    $email = "";
    $description = "";

    if(isset($form_values['customer_email'])){
        
        $email = $form_values['customer_email'];
        
    }
    if(isset($form_values['description'])){
        
        $description = $form_values['description'];
        
    }
    if(isset($form_values['rating'])){
        
        $rating = $form_values['rating'];
        
    }    
    
    if(!empty($email)){
        
        $url = variable_get("eddy_forms_engine_service_domain") . "/FormValidation/EmailCheck/?EmailVerificationLevel=3&EmailAddress=" . urlencode($email) . "&callback=c";
        
        $result = drupal_http_request($url);
        
        if(strpos($result->data, 'false')){
            
            form_set_error('customer_email', "Please enter a valid Email Address.");
            
        }

    }

    if(!empty($description)){
        if(strlen($description) > 3000){
            form_set_error('description', "Maximum length of description is 3000 characters.");
        }
    }
    
}


function get_associate_name($type, $id){
    $associate_name = db_select('eddy_reviews_associate_base', 'b')
         -> fields('b', array('associate_name'))
         -> condition('associate_id', $id, '=')
         -> condition('btype', $type, '=')
         -> execute()->fetchField();

    return $associate_name;
}

function get_associate_link($type, $id){

    if($type =="program"){
        
        return url('institutions/' . $id, array('absolute' => TRUE));
    }else{

         $nid = db_select('field_data_field_external_id', 'ex')
         -> fields('ex', array('entity_id'))
         -> condition('bundle', 'institution', '=')
         -> condition('entity_type', 'node', '=')
         -> condition('field_external_id_value', $id, '=')
         -> execute()->fetchField();

         if(!empty($query)){
             return url(drupal_get_path_alias('node/'.$nid), array('absolute' => TRUE));
         }
        
    }
}