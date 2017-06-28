<?php
function get_qsb_data_load($category_id = '', $subject_id = '', $level_id = '', $question_level = '3', $first_qq = 'level'){		

    $ask_items = array();

	$fields = array(
		//'type' => array(),
		'level' => array(),
		'category' => array(),
		'subject' => array(),
		'qq_level' => $question_level,
        'first_qq' => $first_qq,
	);

	if($level_id != "")
		$fields['level'] = explode(",", $level_id);
    
	if($category_id != "")
		$fields['category'] = explode(",", $category_id);
    
	if($subject_id != "")
		$fields['subject'] = explode(",", $subject_id);
	
    $ask_items = get_data($fields);

	print drupal_json_output(array('total'=>count($ask_items), "ask_items"=>$ask_items));	
	
	drupal_exit();

}

function get_data($fields){
    
    $qs = array_change_key_case(drupal_get_query_parameters(), CASE_LOWER);

	$ask_items = array();
	$num = 0;
	$levels_from_is = array();
	$iss_data = "";
    $result_from_is = array();
    
    $type = $qs['type'];
	try{
        
		//call IS web service
        //only when qdf form type is a url needs to call and compare with ME

        $result_from_is = call_is_service($fields);

		//get drupal taxonomy terms
		$drupal_taxonomy_terms = call_drupal($fields);
        
        $sort_by = get_sort($fields);
		$iss_data = get_iss_data($fields);

        if(count($result_from_is) > 0){            

            if(!empty($drupal_taxonomy_terms)){
                foreach($result_from_is as $result_fis){
                    $ask_id = $result_fis->$iss_data;
                    $terms = find_iss_key_from_drupal_term($ask_id, $drupal_taxonomy_terms);
                    
                    foreach($terms as $key=>$ask_term){
						
                        $listing_url = "";
						$listing_url = get_alias_url($fields, $ask_term['tid'], $ask_term['type']);							                      
						$show_value = $ask_term['value'];	
						$real_title = $ask_term['real_title'];
						$real_value = $ask_term['ext_ids'];
						$ask_items[$show_value] = array('showtitle' => $ask_term['title'], 'real_title' => $real_title, 'showvalue' => $show_value, 'realvalue' => $real_value, "listing_url" => $listing_url);
                        

					}
                    //$middle_time = date('s') . substr((string)microtime(), 1, 7);
                    
                }
            }else{
                
                //use for no taxonomy
                $term_type = get_request_term_type($fields);
                if($term_type == "Level")
                    $term_type = "Program" . $term_type;
                $term_name = $term_type . 'Name';	
                $term_id = $term_type . 'Id';

                foreach($result_from_is as $ask_term){
                    
                    $listing_url = "";
                    $term_title = $ask_term->$term_name;
                    $show_value = $term_title;	
                    $real_title = $term_title;
                    $real_value = $ask_term->$term_id;
                    $ask_items[$show_value] = array('showtitle' => $term_title, 'real_title' => $real_title, 'showvalue' => $show_value, 'realvalue' => $real_value, "listing_url" => $listing_url);
                    
                }
            }
			
		}

	}
    catch (Exception $e) {
		drupal_set_message(t('There was an issue with your configuration in either your tables in your database or WS call.'), 'error');
		dsm($e);
	}
    
	usort($ask_items, $sort_by);

	return $ask_items;
	exit;

}


function sort_by_showvalue($a, $b){
    return strnatcmp(strtolower($a['showvalue']), strtolower($b['showvalue']));
}


function sort_by_title($a, $b){
    return strnatcmp(strtolower($a['showtitle']), strtolower($b['showtitle']));
}



// params -- $find_ext_id: the external id of the taxonomy
//           $taxonomy_terms: taxonomy machine name, find the ext_id from this taxonomy 
// return array -- taxonomy's ext_id and ttle
function find_iss_key_from_drupal_term($find_ext_id = 0, $taxonomy_terms = array()){
	$ask_taxonomy_name = "";
	$ask_taxonomy_term = array();
	$find_it = false;

	if($find_ext_id!=0){
		if(array_key_exists($find_ext_id, $taxonomy_terms)){
			$ask_taxonomy_term = $taxonomy_terms[$find_ext_id];
		}

	}

	return $ask_taxonomy_term;
}
//transfer items from IS to array
function get_request_term_type($fields){
    
    if($fields['first_qq'] == 'level'){

        if(empty($fields['level'])){
            
            return 'Level';	
            
        }elseif(empty($fields['category'])){
            
            return 'Category';
            
        }else{
            if($fields['qq_level'] == '3')
                return 'Subject';
        }
    }elseif($fields['first_qq'] == 'category'){

        if(empty($fields['category'])){
            
            return 'Category';	
            
        }elseif(empty($fields['subject'])){
            return 'Subject';
            
        }else{
            if($fields['qq_level'] == '3')
                return 'Level';
        }
    }
}
// param -- $vacabulary: taxonomy vocabulary machine name
// return array -- taxonomy terms from this taxonomy vocabulary 
function get_taxonomy_terms_from_drupal($vocabulary_name){

	// get all taxonomy terms from the taxonomy vocabulary
	// SQL Statement
	
    //select t.tid, t.name, ex.field_external_id_value, add1.field_external_id_additional_value, qd.field_qsb_display_name_value
    //from (taxonomy_term_data t inner join taxonomy_vocabulary v on v.vid = t.vid)
    //left join field_data_field_external_id ex on t.tid=ex.entity_id
    //left join field_data_field_external_id_additional add1 on t.tid=add1.entity_id
    //left join field_data_field_qsb_display_name qd on t.tid=qd.entity_id
    //left join field_data_field_qsb_enabled en on en.entity_id = t.tid
    //where v.machine_name = 'levels' and en.field_qsb_enabled_value = 1	
	
	$query = db_select('taxonomy_term_data', 't');
    $query->join('taxonomy_vocabulary', 'v', 'v.vid = t.vid');
    if(db_table_exists('field_data_field_qsb_enabled')){
        $query->leftjoin('field_data_field_qsb_enabled', 'en', 'en.entity_id = t.tid');    
    }
    
    if(db_table_exists('field_data_field_legacy_id')){
        $query->leftjoin('field_data_field_legacy_id', 'lg', 'lg.entity_id = t.tid');
        $query->fields('lg', array('field_legacy_id_value'));
    }
    if(db_table_exists('field_data_field_external_id_additional')){
        $query->leftjoin('field_data_field_external_id_additional', 'addex', 'addex.entity_id = t.tid');
        $query->fields('addex', array('field_external_id_additional_value'));
    }
    if(db_table_exists('field_data_field_qsb_display_name')){
        $query->leftjoin('field_data_field_qsb_display_name', 'qd', 'qd.entity_id = t.tid');
        $query->fields('qd', array('field_qsb_display_name_value'));
    }
    if(db_table_exists('field_data_field_qsb_display_value')){
        $query->leftjoin('field_data_field_qsb_display_value', 'qv', 'qv.entity_id = t.tid');
        $query->fields('qv', array('field_qsb_display_value_value'));
    }
    
    if($vocabulary_name == 'categories' && db_table_exists('field_data_field_is_available')){

        $query->leftjoin('field_data_field_is_available', 'ia', 'ia.entity_id = t.tid');        
        $query->leftjoin('field_data_field_category_tr', 'ct', 'ct.entity_id = ia.entity_id');
        $query->leftjoin('taxonomy_term_data', 't2', 't2.tid = ct.field_category_tr_tid');
        $query->leftjoin('field_data_field_external_id', 'ex2', 'ex2.entity_id = t2.tid');
        $query->fields('t2', array('tid','name'));
        $query->fields('ex2', array('field_external_id_value'));
        $query->distinct();
        
        $query->condition('v.machine_name', 'subjects', '=');
        $query->condition('field_is_available_value', 1, '=');
        
    }else{
        if(db_table_exists('field_data_field_external_id')){
            $query->leftjoin('field_data_field_external_id', 'ex', 'ex.entity_id = t.tid');// and (ex.bundle = :parameter1 or ex.bundle = :parameter2 or ex.bundle = :parameter3', array(':parameter1'=> 'levels', ':parameter2'=> 'categories', ':parameter3'=> 'subjects'));
            $query->fields('ex', array('field_external_id_value'));
        }

        if($vocabulary_name == 'subjects' && db_table_exists('field_data_field_is_available')){
            $query->leftjoin('field_data_field_is_available', 'ia', 'ia.entity_id = t.tid');
            $query->condition('v.machine_name', 'subjects', '=');
            $query->condition('field_is_available_value', 1, '=');
        }else{
            $query->condition('v.machine_name', $vocabulary_name, '=');
        }
        
        $query->fields('t', array('tid','name'));
        
    }
    
    //->fields('lg', array('field_legacy_id_value')) 
    //->fields('addex', array('field_external_id_additional_value'))
    //->fields('qd', array('field_qsb_display_name_value'))
    //->fields('qv', array('field_qsb_display_value_value'));
    
    
	
	if($vocabulary_name == 'levels' && db_table_exists('field_data_field_qsb_display_value'))
		$query->condition('en.field_qsb_enabled_value', 1, '=');

    //dpm((string) $query);
    //dpm($query->arguments());
	$result = $query->execute();
    
	//fetchAllKeyed() return an associative array where the key is first column from the result set and the value is another field

	$ask_result = $result->fetchAll();

	$ask_terms = array();
	//$drupal_field = "";

	if(!empty($ask_result)){
		foreach($ask_result as $result_item){
            
			// if additional external id is not available, use external id as additional external id
			// use which field to compare to iis field, set the field value as the key,
			// for levles, have to compare it's additional external id
			if(!empty($result_item->field_external_id_additional_value)){
				$item_key = $result_item->field_external_id_additional_value;		
			}else{
				//$drupal_field = get_drupal_field($vocabulary_name);
				$item_key = $result_item->field_external_id_value;
			}
			
			// get set ext_id according to the $type
			//$drupal_field = get_drupal_field($vocabulary_name);
			$item_ext = $result_item->field_external_id_value;//$drupal_field;
			
			// if qsb display name field is not empty, use it as show title
			if(!empty($result_item->field_qsb_display_name_value)){
				$item_title = $result_item->field_qsb_display_name_value;
			}else{
				$item_title = $result_item->name;
			}
			
			$item_realtitle = $result_item->name;
            if(!empty($result_item->field_legacy_id_value)){
                $item_legacy = $result_item->field_legacy_id_value;
            }else{
                $item_legacy = '';
            }
			// if qsb display value field is not empty, use it as show value				
			if(!empty($result_item->field_qsb_display_value_value)){
				$item_value = $result_item->field_qsb_display_value_value;
			}else{
                
				// from elearners-service.inc
				switch($vocabulary_name){
					case "levels":
						$item_value = $result_item->field_external_id_value;
						break;
					case "categories":
						$item_value = $result_item->name;
						break;
					case "subjects":
						$item_value = $result_item->name;
						break;
				}
			}
			

			
            if(strpos($item_key, ',') !== false ){
				$ext_ids = explode(',',$item_key);
				
				foreach($ext_ids as $ext_id){
					//$ask_terms[$ext_id] = array('ext_ids'=> $item_key, 'title' => $item_val);		
					//$ask_terms[$ext_id] = array();				
					if(!array_key_exists($ext_id, $ask_terms)){
						$ask_terms[$ext_id] = array();
					}
					array_push($ask_terms[$ext_id], array('tid'=>$result_item->tid, 'type'=>$vocabulary_name, 'ext_ids'=> $item_ext, 'legacy_id' => $item_legacy, 'ext_ids_addl'=> $item_key,  'title' => $item_title, 'real_title' => $item_realtitle, "value" => $item_value));
				}
            }
            else{

				if(!array_key_exists($item_key, $ask_terms)){
					$ask_terms[$item_key] = array();
				}
				array_push($ask_terms[$item_key],array('tid'=>$result_item->tid, 'type'=>$vocabulary_name, 'ext_ids'=> $item_ext, 'legacy_id' => $item_legacy, 'ext_ids_addl'=> $item_key, 'title' => $item_title, 'real_title' => $item_realtitle, "value" => $item_value));
			}
		}
	}

	return $ask_terms;//$result->fetchAllKeyed();
}


// param: $vocabulary_name: taxonomy name, such as 'levels', 'categories'
//        $match_id: match_id
// return array: this taxonomy term's additional external id

function get_taxonomy_term_qsb_match_id($vocabulary_name = "", $match_id = ""){

	$ask_field_value = array();
	// initial $ask_field_value value from match_id 
	if(count(explode(",",$match_id)) >1){
		$match_ids = explode(",",$match_id);
		foreach($match_ids as $index=>$id){
			$ask_field_value[$index] = $id;		
		}
	}else{
		$ask_field_value = array('0'=>$match_id);
	}

	return $ask_field_value;
	
}


function get_alias($node_id = ""){
	$ask_alias_url = drupal_get_path_alias("node/".$node_id);
	if(strpos($ask_alias_url, "node/") !== false)
		return "";
	else
		return $ask_alias_url;
	
}



function get_node_alias_level_first($fields, $tid, $term_type){
	
	$ask_alias_url = "";
    
	$query = db_select('node', 'n');

	switch($term_type){
		case 'levels':

			$query->leftjoin('field_data_field_level_tr', 'trl', 'trl.entity_id = n.nid and trl.bundle =:parameter1', array(':parameter1'=>'product_list'));
			$query->condition('trl.field_level_tr_tid', $tid, '=');
			
			$subquery_c = db_select('field_data_field_category_tr', 'c');
			$subquery_c->fields('c', array('entity_id'));
			
			$query->condition('n.nid', $subquery_c, 'NOT IN');
			
			$subquery_s = db_select('field_data_field_subject_tr', 's');
			$subquery_s->fields('s', array('entity_id'));
			
			$query->condition('n.nid', $subquery_s, 'NOT IN');
			break;
        
		case 'categories':

			$query->leftjoin('field_data_field_category_tr', 'trc', 'trc.entity_id = n.nid and trc.bundle =:parameter3', array(':parameter3'=>'product_list'));
			$query->condition('trc.field_category_tr_tid', $tid, '=');
			$query->leftjoin('field_data_field_level_tr', 'trl', 'trl.entity_id = n.nid and trl.bundle =:parameter2', array(':parameter2'=>'product_list'));
			$query->leftjoin('taxonomy_term_data', 'tax', 'tax.tid = trc.field_category_tr_tid or tax.tid = trl.field_level_tr_tid');
			$query->leftjoin('field_data_field_external_id', 'ex', 'ex.entity_id = tax.tid');
			$query->condition('ex.field_external_id_value', $fields['level'][0], '=');
			$query->condition('ex.bundle', 'levels', '=');//);		
            
            
			$subquery_s = db_select('field_data_field_subject_tr', 's');
			$subquery_s->fields('s', array('entity_id'));
			
			$query->condition('n.nid', $subquery_s, 'NOT IN');
			break;
        
		case 'subjects':
			
			$query->leftjoin('field_data_field_subject_tr', 'trs', 'trs.entity_id = n.nid and trs.bundle =:parameter2', array(':parameter2'=>'product_list'));
			$query->condition('trs.field_subject_tr_tid', $tid, '=');
			
			$query->leftjoin('field_data_field_level_tr', 'trl', 'trl.entity_id = n.nid and trl.bundle =:parameter1', array(':parameter1'=>'product_list'));
			$query->leftjoin('field_data_field_category_tr', 'trc', 'trc.entity_id = n.nid and trc.bundle =:parameter3', array(':parameter3'=>'product_list'));
			$query->leftjoin('taxonomy_term_data', 'tax', 'tax.tid = trl.field_level_tr_tid or tax.tid = trc.field_category_tr_tid');
			$query->leftjoin('field_data_field_external_id', 'ex', 'ex.entity_id = tax.tid');
			$query->condition('ex.field_external_id_value', $fields['level'][0], '=');
			$query->condition('ex.bundle', 'levels', '=');//);
            
			break;
		
	}
	if(function_exists('get_campus_type')){
		if(get_campus_type() != ''){
			$query->leftjoin('field_data_field_campus_type_tr', 'trct', 'trct.entity_id = n.nid and trct.bundle =:parameter4', array(':parameter4'=>'product_list'));
			$query->condition('trct.field_campus_type_tr_tid', get_campus_type(), '=');
			$query->condition('trct.entity_type', 'node', '=');
			$query->condition('trct.deleted', 0, '=');
		}else{
			$campus_type_c = db_select('field_data_field_campus_type_tr', 'ctc');
			$campus_type_c->fields('ctc', array('entity_id'));		
			$query->condition('n.nid', $campus_type_c, 'NOT IN');
		}
	}
	$query->condition('n.status', 1, '=');
	$query->fields('n', array('nid', 'title'));
	
	
	$ask_nids = $query->execute()->fetchAll();

	if(!empty($ask_nids) && count($ask_nids) >= 1){
		
		foreach($ask_nids as $ask_nid){
            
			$ask_alias_url = drupal_lookup_path('alias', "node/".$ask_nid->nid);

			if($ask_alias_url != ''){
				break;
			}
		}
	}
	
	return $ask_alias_url;
}	


function get_node_alias_category_first($fields, $tid, $term_type){

	$ask_alias_url = "";
    
	$query = db_select('node', 'n');
	
	switch($term_type){
        
		case 'categories':
			$query->leftjoin('field_data_field_category_tr', 'trc', 'trc.entity_id = n.nid and trc.bundle =:parameter1', array(':parameter1'=>'product_list'));
			$query->condition('trc.field_category_tr_tid', $tid, '=');
			//if(db_table_exists('field_data_field_type_tr')){
			//    $query->leftjoin('field_data_field_type_tr', 'trt', 'trt.entity_id = n.nid and trt.bundle =:parameter4', array(':parameter4'=>'product_list'));
			//    $query->condition('trt.field_type_tr_tid', get_degree_type_tid(), 'in');
			//}
			$subquery_s = db_select('field_data_field_subject_tr', 's');
			$subquery_s->fields('s', array('entity_id'));
			
			$query->condition('n.nid', $subquery_s, 'NOT IN');
			
			$subquery_l = db_select('field_data_field_level_tr', 'l');
			$subquery_l->fields('l', array('entity_id'));
			
			$query->condition('n.nid', $subquery_l, 'NOT IN');
            
			break;
        
		case 'levels':

			//certificate degree type does not save into field_data_field_level_tr table 
			//if(function_exists(get_certificate_level_tid) && $tid != get_certificate_level_tid()){
			
			$query->leftjoin('field_data_field_level_tr', 'trl', 'trl.entity_id = n.nid and trl.bundle =:parameter2', array(':parameter2'=>'product_list'));
			$query->condition('trl.field_level_tr_tid', $tid, '=');
			//}else{
			//    if(db_table_exists('field_data_field_type_tr')){
			//        $query->leftjoin('field_data_field_type_tr', 'trt', 'trt.entity_id = n.nid and trt.bundle =:parameter4', array(':parameter4'=>'product_list'));
			//        //$query->condition('trt.field_type_tr_tid', get_degree_type_tid('certificate'), 'in');
			//    }
			//}
			
			// first load levels
			if($fields['category'] == "0"){
				$subquery_c = db_select('field_data_field_category_tr', 'c');
				$subquery_c->fields('c', array('entity_id'));
                
				$query->condition('n.nid', $subquery_c, 'NOT IN');
                
				$subquery_s = db_select('field_data_field_subject_tr', 's');
				$subquery_s->fields('s', array('entity_id'));
                
				$query->condition('n.nid', $subquery_s, 'NOT IN');
				
			}else{
				
				$query->leftjoin('field_data_field_category_tr', 'trc', 'trc.entity_id = n.nid and trc.bundle =:parameter1', array(':parameter1'=>'product_list'));
				
				// load levels with selected subject
				if(!empty($fields['subject']) && $fields['subject'] != "0"){
					$query->leftjoin('field_data_field_subject_tr', 'trs', 'trs.entity_id = n.nid and trs.bundle =:parameter3', array(':parameter3'=>'product_list'));
					$query->leftjoin('taxonomy_term_data', 'tax', 'tax.tid = trc.field_category_tr_tid or tax.tid = trs.field_subject_tr_tid');
					$query->condition('ex.field_external_id_value', $fields['subject'], '=');
					$query->condition('ex.bundle', 'subjects', '=');//);
					
				}else{

					$query->leftjoin('taxonomy_term_data', 'tax', 'tax.tid = trc.field_category_tr_tid');						
					$query->condition('ex.field_external_id_value', $fields['category'], '=');
					$query->condition('ex.bundle', 'categories', '=');//);
					
					$subquery_s = db_select('field_data_field_subject_tr', 's');
					$subquery_s->fields('s', array('entity_id'));
                    
					$query->condition('n.nid', $subquery_s, 'NOT IN');

				}
				
				$query->leftjoin('field_data_field_external_id', 'ex', 'ex.entity_id = tax.tid');

			}
            
			break;
        
		case 'subjects':

			$query->leftjoin('field_data_field_subject_tr', 'trs', 'trs.entity_id = n.nid and trs.bundle =:parameter3', array(':parameter3'=>'product_list'));
			$query->condition('trs.field_subject_tr_tid', $tid, '=');
			//if(db_table_exists('field_data_field_type_tr')){
			//    $query->leftjoin('field_data_field_type_tr', 'trt', 'trt.entity_id = n.nid and trt.bundle =:parameter4', array(':parameter4'=>'product_list'));
			//    $query->condition('trt.field_type_tr_tid', get_degree_type_tid(), 'in');
			//}						
            $subquery_l = db_select('field_data_field_level_tr', 'l');
            $subquery_l->fields('l', array('entity_id'));
			
			$query->condition('n.nid', $subquery_l, 'NOT IN');
            
			break;
	}

    if(function_exists('get_campus_type')){
		
        if(get_campus_type() != ''){
            
            $query->leftjoin('field_data_field_campus_type_tr', 'trct', 'trct.entity_id = n.nid and trct.bundle =:parameter5', array(':parameter5'=>'product_list'));
            $query->condition('trct.field_campus_type_tr_tid', get_campus_type(), '=');
            $query->condition('trct.entity_type', 'node', '=');
            $query->condition('trct.deleted', 0, '=');
        }else{
            if(db_table_exists('field_data_field_campus_type_tr')){
                $campus_type_c = db_select('field_data_field_campus_type_tr', 'ctc');
                $campus_type_c->fields('ctc', array('entity_id'));		
                $query->condition('n.nid', $campus_type_c, 'NOT IN');
            }
        }
    }
    
	$query->condition('n.status', 1, '=');
	$query->fields('n', array('nid', 'title'));
    //
	//$query->distinct();

	$ask_nids = $query->execute()->fetchAll();

	if(!empty($ask_nids) && count($ask_nids) >= 1){
		
		foreach($ask_nids as $ask_nid){
            
			$ask_alias_url = drupal_lookup_path('alias', "node/".$ask_nid->nid);

			if($ask_alias_url != ''){
				break;
			}
		}
	}
    
	return $ask_alias_url;
}


function call_is_service_category_first($fields){	
	
	$method = "";
	
	if(empty($fields['category'])){
        
		$method = "GetCategories";
		
	}elseif(empty($fields['subject'])){
        
		$method = "GetSubjects";
        
	}elseif(empty($fields['level'])){
        
		$method = "GetProgramLevels";
	}
    
	$results = qsb_service_results($fields, $method);
	return $results;
    
}



function call_is_service_level_first($fields){	
	
	$method = "";
	
	if(empty($fields['level'])){
        
		$method = "GetProgramLevels";
		
	}elseif(empty($fields['category'])){
        
		$method = "GetCategories";
        
	}elseif(empty($fields['subject'])){
        
		$method = "GetSubjects";
	}

	
	$results = qsb_service_results($fields, $method);
	
	return $results;
}



function qsb_service_results($fields, $method){

	$results = null;

	$output = null;

    //to improve speed up of loading first field
    //cache first field
    if(empty($fields[$fields['first_qq']])){
        $cid = get_current_state() . '_eddy_qsb_' . $fields['first_qq'] . $_COOKIE['_CampaignTrackID'];
    }else{
        $cid = '';
    }

	$cacheOptions = array(
		'cid' => $cid,
		'table' => 'cache_eddy_qsb_data',
		'duration' => time() + 9000,
		'enabled' => TRUE, //Disabled for Testing
	);
	
	//[version 1]since currently directories doesn't support campus form template, if qdf direct a campus form result to directories will cause error for eL.
	//[version 1]solution:	hardcoded for hotfix the only load online degree, online category and online subject for qdf until directories support campus
    //[version 2]remove Campus Type for only GS to fix 66161, eLearners and EMD still need it
	//$fields['campus_type'] = array('0'=>1);
	
	//filter out those items that program gets capped out
	$fields['remove_capped'] = true;

	
	if(!empty($_COOKIE['_CampaignTrackID']) && $_COOKIE['_CampaignTrackID'] != variable_get('eddy_core_track_id')){
		
		$fields['track_id'] = $_COOKIE['_CampaignTrackID'];
		$cacheOptions['enabled'] = FALSE;
		
	}

    //to improve speed up of loading first field
    //cache first field no matter "eddy_services_cache_is_enabled" value
    if ($cacheOptions['cid'] != '' && $cache = cache_get($cid, $cacheOptions['table'])){

        if ($cache->expire > REQUEST_TIME)
            $results = $cache->data;
        else
            $results = eddy_services_get_listings($fields, $method, $cacheOptions);
        
    }else{
		$results = eddy_services_get_listings($fields, $method, $cacheOptions);
        
        if($cacheOptions['cid'] != ''){
            cache_set($cid, $results, $cacheOptions['table']);
        }
            
	}	
	
	
	if(!empty($results->GetProgramLevelsResult->ProgramLevelList)){
		$output = $results->GetProgramLevelsResult->ProgramLevelList;
	}
	
	else if(!empty($results->GetCategoriesResult->CategoryList)){
		$output = $results->GetCategoriesResult->CategoryList;
	}
	
	else if(!empty($results->GetSubjectsResult->SubjectList)){
		$output = $results->GetSubjectsResult->SubjectList;
	}
	
	return $output;


}




function call_drupal($fields){	

	if($fields['first_qq'] == 'level'){

		if(empty($fields['level'])){
            
			return get_taxonomy_terms_from_drupal('levels');	
			
		}elseif(empty($fields['category'])){
            
			return get_taxonomy_terms_from_drupal('categories');
			
		}else{
		    if($fields['qq_level'] == '3')
			    return get_taxonomy_terms_from_drupal('subjects');
            
		}
    }elseif($fields['first_qq'] == 'category'){

        if(empty($fields['category'])){
			return get_taxonomy_terms_from_drupal('categories');	
			
		}elseif(empty($fields['subject'])){
			return get_taxonomy_terms_from_drupal('subjects');
			
		}else{
            if($fields['qq_level'] == '3')
			    return get_taxonomy_terms_from_drupal('levels');
        }
    }

}

function get_iss_data($fields){
	if($fields['first_qq'] == 'level'){
        
		if(empty($fields['level'])){
            
			return "ProgramLevelId"; //get_iss_field('levels');	
			
		}elseif(empty($fields['category'])){
            
			return "CategoryId"; //get_iss_field('categories');	
			
		}elseif($fields['qq_level'] == '3'){
            
			return "SubjectId"; //get_iss_field('subjects');
			
		}
		
	}else{
        
		if(empty($fields['category'])){
            
			return "CategoryId"; //get_iss_field('categories');	
			
		}elseif(empty($fields['subject'])){
            
			return "SubjectId"; //get_iss_field('subjects');
			
		}elseif($fields['qq_level'] == '3'){
            return "ProgramLevelId"; //get_iss_field('levels');	
        }
	}
}

function get_alias_url($fields, $tid, $term_type){

	if($fields['first_qq'] == 'level'){
		if(!empty($fields['level'])){							

			return get_node_alias_by_terms($fields, $tid, $term_type);								
            
		}else{

            return "";
            
		}
	}else{
        
		if(!empty($fields['category'])){							

            return get_node_alias_by_terms($fields, $tid, $term_type);								
            
		}else{

			return "";
            
		}
	}
}




function get_node_alias_by_terms($fields, $tid, $term_type){

	if($fields['first_qq'] == 'level'){
		$ask_alias_url = get_node_alias_level_first($fields, $tid, $term_type);
	}else{
		$ask_alias_url = get_node_alias_category_first($fields, $tid, $term_type);
	}
	return $ask_alias_url;
	
}	