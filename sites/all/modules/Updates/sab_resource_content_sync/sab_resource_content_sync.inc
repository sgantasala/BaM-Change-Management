<?php



function sab_resources_sync () {
    dpm('test again');
 
     try{
         db_set_active('sab_new');
        
         $results = db_select('sa_vw_resources', 'c')
         ->fields('c')
         //->condition('ParentCategoryID', null)
         //->orderBy('CategoryID', 'asc')
         ->execute()
         ->fetchAll();
        
        db_set_active();
        dpm($results);
        
        foreach($results as $k => $v){
              $resource = new stdclass();
                 
              $resource->type = "resources"; // Or page, or whatever content type you like

              node_object_prepare($resource); // Set some default values

              $resource->title = $v->Title;
              $resource->language = LANGUAGE_NONE; // Or e.g. 'en' if locale is enabled
 
     
    
            $resource->body[$resource->language][0]['value'] = $v->Content;
             $resource->body[$resource->language][0]['summary'] = '';
            $resource->body[$resource->language][0]['format']  = 'full_html';
             $resource->field_postname[$resource->language][0]['value']=$v->PostName;
             //$resource->field_threadid[$resource->language][0]['value']=$v->ThreadID;

 
       $resource->comment = 1;
          if($resource = node_submit($resource)) { // Prepare node for saving
       node_save($resource);
          echo "Node with nid " . $resource->nid . " saved!\n";
    }
 


  }
   }
      catch(Exception $e){
        dpm($e);
        db_set_active();
    }
   
 }
 function sab_article_sync() {

 
 
    $node = new stdClass(); // Create a new node object
    $node->type = "article"; // Or page, or whatever content type you like

    node_object_prepare($node); // Set some default values

    $node->title    = "articlestest";
    $node->language = LANGUAGE_NONE; // Or e.g. 'en' if locale is enabled
 

  
    
    $node->body[$node->language][0]['value'] = 'Body asdalsdfa;lsdf;asd;fjas;djlf;sadfj;alsdfl;asdfjdsalf';
    $node->body[$node->language][0]['summary'] = '';
    $node->body[$node->language][0]['format']  = 'filtered_html';

//    // Example if using custom fields
//$node->field_CUSTOM_FIELD[$node->language][0]['value'] = 'Value';
//// Example if using fields that are taxonomy type
//$node->field_CUSTOM_FIELD_TAXONOMY[$node->language][0]['tid'] = 1;

    $path = 'node_created_on' . date('YmdHis');
    $node->path = array('alias' => $path);
    $node->comment = 1;
    if($node = node_submit($node)) { // Prepare node for saving
      node_save($node);
      echo "Node with nid " . $node->nid . " saved!\n";
    }
    dpm('test');


}
