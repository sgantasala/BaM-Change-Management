<?php

/**
 * @file
 * Views integration and data for the sab reviews module.
 */

/**
 * Implements hook_views_data_alter(&$data).
 * declare views fields
 */

function eddy_reviews_views_data_alter(&$data) {
    
    $data['eddy_reviews']['table']['join'] = array(
      'reviews_associate_base' => array(
          'left_field' => 'bid',
          'field' => 'bid',
      ),
      'user' => array(
          'left_field' => 'updated_uid',
          'field' => 'uid',
      ),
    );

    $data['eddy_reviews']['bid'] = array(
      'title' => t('Program/Institution ID'),
      'help' => t('ID of program/institution which related to the review.'),
      'field' => array(
          'handler' => 'views_handler_field',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_string',
      ),
      'relationship' => array(
          'base' => 'eddy_reviews_associate_base',
          'base field' => 'bid',
          'field' => 'bid',
          'handler' => 'views_handler_relationship',
          'label' => t('Associate Info'),
      ),

    );
    $data['eddy_reviews']['updated_uid'] = array(
        'title' => t('Review Updated by User ID'),
        'help' => t('Relate reviews to the user who change/update it.'),
        'field' => array(
          'handler' => 'views_handler_field_user',
          ),
          'filter' => array(
              'handler' => 'views_handler_filter_numeric',
            ),
        'relationship' => array(
            'base' => 'users',
            'base field' => 'uid',
            'field' => 'updated_uid',
            'handler' => 'views_handler_relationship',
            'label' => t('Changed By'),
        ),
    );
    
}