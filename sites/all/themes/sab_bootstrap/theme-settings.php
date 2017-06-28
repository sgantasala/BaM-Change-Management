<?php
/**
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function sab_bootstrap_form_system_theme_settings_alter(&$form, $form_state) {

    /*
   * Create the form using Forms API
  */
  //Content Display
	$form['content_display'] = array(
	  '#type'          => 'fieldset',
	  '#title'         => t('Content Display'),
	);
	$form['content_display']['mobile_hide_program_content_over_char'] = array(
      '#type' => 'textfield',
	  '#title'         => t('Mobile: Hide Program Content When Over above Charactars.'),
	  '#default_value' => theme_get_setting('mobile_hide_program_content_over_char'),
	);
 
}
