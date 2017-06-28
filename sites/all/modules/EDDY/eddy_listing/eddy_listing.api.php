<?php

/**
 * Alter list from EDDY Listings Response
 *
 * @param &$list (Alterable)
 *   A Listing from Matching Engine
 * @param $list_fields
 *   Listing Properties from the EDDY Listings Module.
 */
function hook_eddy_listing_list_result_alter(&$list, $list_fields) {
    dpm($list);
    dpm($list_fields);
}

/**
 * Alter options for an EDDY Listings Request
 *
 * @param &$options (Alterable)
 * an Array of Options which will be passed to eddy_services_get_listings()
 * 
 * @param $list_fields
 *   Listing Properties from the EDDY Listings Module.
 */
function hook_eddy_listing_list_request_alter(&$options, $list_fields) {
    dpm($options);
    dpm($list_fields);
}

/**
 * Do something when a list is Inserted
 *
 * @param $form
 * Form Array
 * 
 * @param $form_state
 *   Form State Array
 *   
 * @param $lid
 *   List ID
 */
function hook_eddy_listing_insert($form, $form_state, $lid){

    dpm($form);
    dpm($form_state);
    dpm($lid);

}

/**
 * Do something when a list is Updated
 *
 * @param $form
 * Form Array
 * 
 * @param $form_state
 *   Form State Array
 *   
 * @param $lid
 *   List ID
 */
function hook_eddy_listing_update($form, $form_state, $lid){

    dpm($form);
    dpm($form_state);
    dpm($lid);

}

/**
 * Do something when a list is Deleted
 *
 * @param $list
 * List Array
 */
function hook_eddy_listing_delete($list){

    dpm($list);

}