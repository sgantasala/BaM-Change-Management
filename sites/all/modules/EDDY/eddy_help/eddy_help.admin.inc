<?php

function _eddy_help_edit_form($form, &$form_state, $action, $id = 0) {

	$result = new stdclass();

	if($action == 'edit' && $id > 0){
		
		$results = eddy_help_get_item_by_id($id);
		
		$form['item_id']['#value'] = $id;
	}
	
	$form['title'] = array(
	  '#type' => 'textfield', 
	  '#title' => t('Title'), 
	  '#default_value' => (!empty($result->title)) ? $result->title : '', 
	  '#size' => 60,
	  '#maxlength' => 128, 
	  '#required' => TRUE,
	);
	
	$form['description'] = array(
	  '#type' => 'textarea', 
	  '#title' => t('Description'), 
	  '#default_value' => (!empty($result->description)) ? $result->description : '',
	);
	
	$form['actions'] = array('#type' => 'actions');
	
	if($action == 'add'){
		
		$form['actions']['update'] = array(
			'#type' => 'submit',
			'#value' => t('Create'),
			'#submit' => array('_eddy_help_create_item'),
		);
	
	}else{
	
		$form['actions']['update'] = array(
			'#type' => 'submit',
			'#value' => t('Update'),
			'#submit' => array('_eddy_help_update_item'),
		);

		$form['actions']['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete'),
			//'#access' => $type == 'edit',
			'#submit' => array('_eddy_help_delete_item'),
		);
		
	}
	
	return $form;
 
}


function _eddy_help_create_item($form, &$form_state){

	global $user;

	$fields = $form_state['values'];
	
	try{
	
		$fields = array(
			'title' => $fields['title'],
			'description' => $fields['description'],
			'uid' => $user->uid,
			'status' => 1,
			'created' => REQUEST_TIME,
			'changed' => REQUEST_TIME,
		);
		
		db_insert('eddy_help')
		->fields($fields)
		->execute();
		
		drupal_set_message("Your Help Term was created.");
		drupal_goto('eddy-help');
	}
	catch (Exception $e)
	{
		drupal_set_message(t('There was an issue inserting this record.'), 'error');
		dpm($e);
	}

}


function _eddy_help_update_item($form, &$form_state){

	$fields = $form_state['values'];

	try{
	
		$fields = array(
			'title' => $fields['title'],
			'description' => $fields['description'],
			'changed' => REQUEST_TIME,
		);
		
		db_update('eddy_help')
		->fields($fields)
		->condition('id', $form['item_id']['#value'])
		->execute();
		
		drupal_set_message("Your Help Term was updated.");
		drupal_goto('eddy-help');
	}
	catch (Exception $e)
	{
		drupal_set_message(t('There was an issue updating this record.'), 'error');
		dpm($e);
	}
	
}

/**
 * Form Callback: Displays Confirmation Message.
 */
function _eddy_help_delete_item($form, &$form_state){

	$form_state['redirect'] = 'eddy-help/' . $form['item_id']['#value'] . '/delete';

}


/**
 * Menu Callback: Displays Confirmation Message.
 */
function _eddy_help_delete_confirm($form, &$form_state, $id) {

	$item = eddy_help_get_item_by_id($id);
	
	$caption = '<p>' . t('This action cannot be undone.') . '</p>';
	$message = t('Are you sure you want to delete this Help Item: %title?', array('%title' => $item->title));
	
	return confirm_form($form, $message, 'eddy-help/' . $item->id . '/edit', $caption, t('Delete'));
	
}

/**
 * Implements hook_submit.
 */
function _eddy_help_delete_confirm_submit($form, &$form_state){

	if(is_numeric(arg(1))){
		
		db_delete('eddy_help')
		->condition('id', arg(1))
		->execute();
		
		drupal_set_message("Your entry has been deleted.");
		drupal_goto("eddy-help");
		
	}else{
	
		drupal_goto("eddy-help");
		
	}
	
}


function eddy_help_get_item_by_id($id){

	return db_select('eddy_help', 'e')
		->fields('e')
		->condition('id', $id)
		->execute()
		->fetchObject();
	
}