<?php
/**
 * @file
 * Metatag integration for the Metatag:Facebook module.
 */

/**
 * Implements hook_metatag_info().
 */
function eddy_metatag_metatag_info() {
  
  $info['groups']['eddy'] = array(
    'label' => t('EDDY'),
    'description' => t("Custom Meta Tags for EDDY."),
    'form' => array(
      '#weight' => 100,
    ),
  );
  
  $info['tags']['open_field:field'] = array(
    'label' => t('HTML'),
    'form' => array(
      '#type' => 'textarea',
      '#rows' => 10,
      '#wysiwyg' => FALSE,
    ),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'eddy',
    //'element' => array(
    //  '#theme' => 'metatag_head_item',
    //),
  );

  return $info;
  
}
