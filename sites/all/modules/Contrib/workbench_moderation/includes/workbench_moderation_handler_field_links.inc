<?php

/**
 * @file
 * Provides moderation links for Views.
 */

class workbench_moderation_handler_field_links extends views_handler_field {
  function render($values) {

	if ($values->{$this->aliases['is_current']}) {
      
	  $node = node_load($values->{$this->aliases['nid']}, $values->{$this->aliases['vid']});
	  $wbLinks =(workbench_moderation_get_moderation_links($node, array('query' => array('destination' => $_GET['q']))));
	  
	  foreach($wbLinks as $link){
		$safeValue = explode('/',$link['href']);
		
		if($node->type != 'school' && $safeValue[5] == 'beta')
			unset($link);
		
		if(isset($link['title']))
			$links[] = $link;
		
	  }
	  
	  return theme('links', array('links' => $links));
	
	}
    return '';
  }
}
