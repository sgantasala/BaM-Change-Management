<?php

/**
 * @file
 * Administrative page callbacks for Popular Cities & Countries.
 */
 
function sab_popular_city_filter_form() {
  
    $filter_options = array(); 
    $countries = get_sab_sitemap_terms_list('countries') ;
    
    foreach($countries as $country) {
        $filter_options[$country->tid] = $country->name; 
    }

    $filter_options[''] = '-ALL-'; 

    $form['filters'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>',
      '#attributes' => array(
        'class' => array('list-operations'),
      ),
    );

    $form['filters']['country'] = array(
      '#type' => 'select',
      '#options' => $filter_options,
      '#title' => 'Filter by Country',
      '#default_value' => isset($_SESSION['popular_city_filter']) ? $_SESSION['popular_city_filter'] : '', 
    );
    $form['filters']['submit'] = array(
     '#type' => 'submit',
     '#value' => t('Filter'),
     '#submit' => array('sab_popular_city_filter_submit'),
    );

    return $form;
}

/**
 * Process result filter from.
 */
function sab_popular_city_filter_submit($form, &$form_state) {
 
    $_SESSION['popular_city_filter'] = $form_state['values']['country'];
   
    $form_state['redirect'] = 'admin/structure/popular_city_country/manage/city';
    
    return;
}

function sab_popular_city_list_form($form, &$form_state) {
 
    if (module_exists('overlay') && overlay_get_mode() == 'child') {
        
        $form_state['rebuild'] = TRUE;
        
        $current_path = current_path();
        
        overlay_close_dialog($current_path, 
           array('query' => drupal_get_query_parameters(NULL, array('q', 'render'))));
        
        $form_state['redirect'] = FALSE;
        
    }

    // Set up the header.
    $header = array(
        'city' => array('data' => t('City') ),
        'country' => array('data' => t('Country') ),
    );
  
    // Get filter keys and add the filter form.
    $keys = func_get_args();
    $keys = array_splice($keys, 2); // Offset the $form and $form_state parameters.
    $keys = implode('/', $keys);
    
    // Build the 'Update options' form.
    $form['operations'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>',
      '#attributes' => array(
        'class' => array('list-operations'),
      ),
    );

    $form['operations']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('sab_popular_city_list_form_submit'),
    );

    // Building the SQL query to load the cities.
    $query = db_select('taxonomy_term_data', 'c');
    $query->join('field_data_field_country_tr', 'ct', 'ct.entity_id = c.tid');
    $query->join('taxonomy_vocabulary', 'v', 'v.vid = c.vid');
    $query->join('taxonomy_term_data', 'cty', 'cty.tid = ct.field_country_tr_tid');
    $query->condition('v.machine_name', 'cities');
   
    if(!empty($_SESSION['popular_city_filter'])) {
        $query->condition('ct.field_country_tr_tid', $_SESSION['popular_city_filter']); 
    }

    $query->fields('c', array('tid')); 
    $query = $query->extend('PagerDefault')->limit(500); 

    $query->orderBy('cty.name', 'ASC');
    $query->orderBy('c.name', 'ASC');
 
    $tids = $query->execute()->fetchCol();

    $cities= sab_popular_city_country_load_multiple($tids);
    
    $rows = array();
    $default_values = array(); 
    
    foreach ($cities as $tid => $city) {
      
        $country_term = taxonomy_term_load($city->field_country_tr['und'][0]['tid']);
        $country = $country_term->name;
        
        $row = array();

        $row['city'] = $city->name;
        $row['country'] = $country;

        $rows[$tid] = $row;

        if(!empty($city->field_is_popular['und'][0]['value']) && $city->field_is_popular['und'][0]['value'] == TRUE) {
            $default_values[$tid] = TRUE; 
        }
        
    }

    $form['tids'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $rows,
      '#default_value' => $default_values, 
      '#empty' => t('No Cities available.'),
      '#attributes' => array(
        'class' => array('popular-list-tableselect'),
      ),
    );
  
    $form['pager'] = array('#theme' => 'pager');
  
    return $form;
}

function sab_popular_city_country_load_multiple($tids = array(), array $conditions = array(), $reset = FALSE) {
    return taxonomy_term_load_multiple($tids, $conditions, $reset);
}

function sab_popular_city_list_form_alter(&$form, &$form_state, $form_id) {
    //Validation errors for the city list update need to be ignored  
    if ($form_id == 'sab_popular_city_list_form') {
        unset($form['#validate']);

        $form['operations']['submit']['#limit_validation_errors'] = array();
        $form['submit']['#limit_validation_errors'] = array();
    }
    
}

function sab_popular_city_list_form_submit($form, &$form_state) {
  
    // Filter out unchecked terms 
    $tids = array_filter($form_state['values']['tids']);
    
    $diff = array_diff($form_state['values']['tids'], $tids);

    $unset_tids = array(); 

    foreach($diff as $k=>$v){
        $unset_tids[] = $k; 
    }

    sab_popular_city_update($tids, $unset_tids); 
    cache_clear_all('city:', 'cache_sab_faceted_nav', TRUE);
    cache_clear_all('product_list/*', 'cache_sab_faceted_nav', TRUE);
    cache_clear_all('node/*', 'cache_sab_faceted_nav', TRUE);

    $count = count($form_state['values']['tids']);
    watchdog('sab_popular_city_country', '@action', array('@action' => 'Popular Cities Updated', '@count' => $count));
    drupal_set_message(format_plural(count($tids), '@action.', '@action', array('@action' => 'Popular Cities Updated', '@count' => $count)));

}


/**
 * Form callback which shows an overview page of all the custom Forms and their descriptions.
 */

function sab_popular_country_list_form($form, &$form_state) {
    
    // Set up the header.
    $header = array(
        'country' => array('data' => t('Country')),
    );
  
    // Get filter keys and add the filter form.
    $keys = func_get_args();
    $keys = array_splice($keys, 2); // Offset the $form and $form_state parameters.
    $keys = implode('/', $keys);
    
    // Build the 'Update options' form.
    $form['operations'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>',
      '#attributes' => array(
        'class' => array('list-operations'),
      ),
    );
  
    $form['operations']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
      '#submit' => array('sab_popular_country_list_form_submit'),
    );

    // Building the SQL query to load the countries.
    $query = db_select('taxonomy_term_data', 'c');
    $query->join('taxonomy_vocabulary', 'v', 'v.vid = c.vid');
    $query->leftJoin('field_data_field_is_popular', 'e', "e.entity_id = c.tid and e.entity_type = 'taxonomy_term'");
    $query->condition('v.machine_name', 'countries');
    $query->fields('c', array('tid')); 
    $query->fields('e', array('field_is_popular_value'));
    $query->orderBy('c.name');

    $tids = $query->execute()->fetchCol();
   
    $countries= sab_popular_city_country_load_multiple($tids);
    
    $rows = array();
    $default_values = array(); 

    foreach ($countries as $tid => $country) {
        
        $row = array();
         
        $row['country'] = $country->name;
        
        $rows[$tid] = $row; 

        if(!empty($country->field_is_popular['und'][0]['value']) && $country->field_is_popular['und'][0]['value'] == TRUE) {
            $default_values[$tid] = TRUE; 
        }
    }
    
    $form['tids'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $rows,
      '#empty' => t('No Countries available.'),
      '#default_value' => $default_values, 
      '#attributes' => array(
        'class' => array('popular-list-tableselect'),
      ),
    );

    return $form;

}

function sab_popular_country_list_form_submit($form, &$form_state) {

    // Filter out unchecked terms 
    $tids = array_filter($form_state['values']['tids']);
    
    $diff = array_diff($form_state['values']['tids'], $tids);

    $unset_tids = array(); 

    foreach($diff as $k=>$v){
        $unset_tids[] = $k; 
    }

    sab_popular_country_update($tids, $unset_tids);    
    cache_clear_all('country:', 'cache_sab_faceted_nav', TRUE);
    cache_clear_all('/', 'cache_sab_faceted_nav', TRUE);

    $count = count($form_state['values']['tids']);
    watchdog('sab_popular_city_country', '@action', array('@action' => 'Popular Countries Updated.', '@count' => $count));
    drupal_set_message(format_plural(count($tids), '@action', '@action', array('@action' => 'Popular Countries Updated.', '@count' => $count)));

}

