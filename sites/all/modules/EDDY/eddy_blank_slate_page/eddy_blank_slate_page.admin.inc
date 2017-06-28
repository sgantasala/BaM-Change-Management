<?php

/**
 * Clone callback; Build the short form that handles the cloning of a landing page.
 */
function eddy_blank_slate_page_clone_page($form, &$form_state) {

	$form['title'] = array(
		'#type' => 'textfield',
		'#title' => t('Admin title(Not displayed)'),
		'#required' => TRUE,
	);

	$form['page_name'] = array(
		'#type' => 'textfield',
		'#title' => t('Page Name(URL alias)'),
		'#description' => t('This page name will be what builds the url for the landing page.<br>For example: www.educationdynamics.com/landingpages/[page-name]'),
		'#required' => TRUE,
	);

    $form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#submit' => array('eddy_blank_slate_page_clone_submit'),
	);

	$form['actions']['cancel'] = array(
		'#type' => 'submit',
		'#limit_validation_errors' => array(),
		'#value' => t('Cancel'),
		'#submit' => array('eddy_blank_slate_page_clone_cancel'),
	);

	return $form;

}

function eddy_blank_slate_page_clone_submit($form, &$form_state) {

	//Handle the submit function
	$new_node = node_load(arg(1));

	$title = $form_state['values']['title'];
	$page_name = $form_state['values']['page_name'];

	unset($new_node->nid);
	unset($new_node->vid);

	$new_node->title = $title;
	$new_node->field_page_name[$new_node->language][0]['value'] = $page_name;
	$new_node->field_page_name[$new_node->language][0]['safe_value'] = $page_name;
	$new_node->is_new = TRUE;

	$url = eddy_blank_slate_page_get_url($new_node);

	$exists = db_query('SELECT 1 FROM {url_alias} WHERE alias = :url', array(':url' => $url))->fetchField();

	if ($exists) {
		drupal_set_message(t('There already exists a landing page with that page name.  Please use a different page name.'), 'error');
	}
	else {

		node_object_prepare($new_node);
		$node = node_submit($new_node);
		node_save($new_node);

		drupal_goto(url('node/'.$new_node->nid));

	}

}

function eddy_blank_slate_page_clone_cancel($form, &$form_state) {

	drupal_goto(url('node/'.arg(1)));

}