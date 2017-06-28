<?php

/**
 * Callback function for displaying the individual project page
 */
function eddy_reviews_setting($form, &$form_state) {
    
    //set page title
    drupal_set_title(t('Review Settings'));
    $form['setting']['eddy_reviews_product_list_criteria'] = array(
      '#title' => t('Filter Review Criteria on Product List Page:'),
      '#description' => t('Seperate multiple criteria by ",". The most closely match the criteria put at the first place. The available filters are type, city, country, institution, level, category, subject, specialty'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eddy_reviews_product_list_criteria')?variable_get('eddy_reviews_product_list_criteria'):'type, city, country',
      '#required' => TRUE,
    );
    $form['setting']['eddy_reviews_notice_email'] = array(
      '#title' => t('Automated Email:'),
      '#description' => t('Once a review submited, an automated email will be sent to this administrator.'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eddy_reviews_notice_email')?variable_get('eddy_reviews_notice_email'):'vboyle@educationdynamics.com',
      '#required' => TRUE,
    );
    $form['setting']['eddy_reviews_recent_count'] = array(
      '#title' => t('Recent Review Display Count:'),
      '#description' => t('This is a numeric only value which will determines how many reviews to display in widget on <strong>program listing page</strong>.'),
      '#type' => 'textfield',
      '#default_value' => variable_get('eddy_reviews_recent_count')?variable_get('eddy_reviews_recent_count'):'5',
      '#required' => TRUE,
    );
    $form['setting']['eddy_reviews_on_detail_count'] = array(
        '#title' => t('Review Display Count on Program Detail:'),
        '#description' => t('This is a numeric only value which will determines how many reviews to display in widget on <strong>program detail page</strong>.'),
        '#type' => 'textfield',
        '#default_value' => variable_get('eddy_reviews_on_detail_count')?variable_get('eddy_reviews_on_detail_count'):'5',
        '#required' => TRUE,
    );  

    $form['setting']['eddy_reviews_character_count'] = array(
            '#title' => t('Review Description Word Count:'),
            '#description' => t('This is a numeric only value which will determines how many characters to display in widget on program detail page.'),
            '#type' => 'textfield',
            '#default_value' => variable_get('eddy_reviews_character_count')?variable_get('eddy_reviews_character_count'):'250',
            '#required' => TRUE,
        );  
    $form['setting']['eddy_reviews_read_more_text'] = array(
                '#title' => t('Review Description Read More Text:'),
                '#type' => 'textfield',
                '#default_value' => variable_get('eddy_reviews_read_more_text')?variable_get('eddy_reviews_read_more_text'):'read more',
                '#required' => TRUE,
            );  

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Setting'),
    );

    

    return $form;

}


/**
 * Process review edit form submissions.
 */
function eddy_reviews_setting_submit($form, &$form_state) {

    $settings = $form_state['values'];
    variable_set('eddy_reviews_product_list_criteria', $settings['eddy_reviews_product_list_criteria']);
    variable_set('eddy_reviews_recent_count', $settings['eddy_reviews_recent_count']);
    variable_set('eddy_reviews_on_detail_count', $settings['eddy_reviews_on_detail_count']);
    variable_set('eddy_reviews_character_count', $settings['eddy_reviews_character_count']);
    variable_set('eddy_reviews_read_more_text', $settings['eddy_reviews_read_more_text']);
    variable_set('eddy_reviews_notice_email', $settings['eddy_reviews_notice_email']);

    drupal_set_message(t('Review settings have been saved.'));

    $form_state['redirect'] = EDDY_REVIEW_ADMIN_PATH;
    
}


