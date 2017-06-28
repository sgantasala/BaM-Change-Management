<?php

/**
 * Alter the FormsEngine Associative Array before it becomes a string.
 *
 * @param &$form_engine (Array)
 *   An associative array of the FormsEngine properties.
 */
function hook_eddy_forms_engine_build_alter(&$form_engine) {
    dpm($form_engine);
}

/**
 * Alter the FormsEngine JavaScript Object before it is printed on the page.
 *
 * @param &$rendered_form (String)
 *   Rendered JavaScript Object (String)
 */
function hook_eddy_forms_engine_alter(&$rendered_form) {
    dpm($rendered_form);
}