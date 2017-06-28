<?php

/**
 * Provides custom form settngs.
 */
function eddy_core_custom_site_settings_form($form, &$form_state) {
  
   $options = array(
      0 => t('Select an Application'),
      1 => t('Universities Abroad'),
      2 => t('eLearners'),
      6 => t('Earn My Degree'),
      7 => t('GradSchools'),
      10 => t('Education Connection'),
      16 => t('Microsites'),
   );

   try{

       db_set_active('nexus'); 

       $results = db_select('Application', 'a')->fields('a')->execute()->fetchAll();

       db_set_active();

       $options[0] = t('Select an Application');

       foreach($results as $v){
       
           $options[$v->ApplicationId] = t($v->ApplicationName);
       
       }
   
   }catch(Exception $e){
   
        db_set_active();

        if(module_exists('devel')){
            dpm($e);
        }
   
   }


  $form['application_id'] = array(
    '#type' => 'select',
    '#title' => t('Application Name'),
    '#required' => TRUE,
    '#options' => $options,
    '#description' => t('This will determine the <strong>IS</strong> application ID that this site is bound to. You can retrieve this value in your module by using: <strong>variable_get(\'eddy_core_application_id\');</strong>'),
    '#default_value' => variable_get('eddy_core_application_id'),
  );

  //Should not be needed, will need to take a look.
  $form['beta_is_enabled'] = array(
	'#type' => 'checkbox',
	'#title' => t('Enable Beta environment for School and Program content.'),
	'#description' => t('If the Workbench Moderation Module is active and has a "Beta" state then this feature can be used to present beta content when a user is on the "http://beta." sub domain. You can retrieve this value in your module by using: <strong>variable_get(\'eddy_core_beta_is_enabled\');</strong>'),
	'#default_value' => variable_get('eddy_core_beta_is_enabled'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
	'#weight' => 9999,
  );

  return $form;

}

function eddy_core_custom_site_settings_form_validate($form, &$form_state) {
  
  if ($form_state['values']['beta_is_enabled'] && module_exists('workbench_moderation')){
	
	$betaState = db_query("SELECT w.name FROM {workbench_moderation_states} w  WHERE w.name = 'beta'")->fetchField();

	if(!empty($betaState)){
		form_set_error('', t('Please make sure Workbench Moderation is installed and there is "beta" state created.'));
		return false;
	}
	
  }
  
  //Removed this condition becuase a site may not have beta.
  //else{
  
  //  form_set_error('', t('Please make sure Workbench Moderation is installed and there is "beta" state created.'));
	
  //}
  
}

function eddy_core_custom_site_settings_form_submit($form, &$form_state){

  //Creating Machine name for Application Names
  $appID = $form_state['values']['application_id'];
  $appName = $form['application_id']['#options'][$appID];
  $appName = strtolower($appName);
  $appName = str_replace(' ','_', $appName);

	//Setting All Varibles
	variable_set('eddy_core_application_id', $appID);
	variable_set('eddy_core_application_name', $appName);
	variable_set('eddy_core_beta_is_enabled', $form_state['values']['beta_is_enabled']);
	
	drupal_set_message(t('The site settings have been saved.'));
	
}