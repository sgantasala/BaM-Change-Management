<?php
module_load_include('inc', 'eddy_qsb', 'service-include/eddy_qsb_service');

function get_qsb_data($level_id = '', $category_id = '', $subject_id = ''){	
	
	get_qsb_data_load($category_id, $subject_id, $level_id);
}	

function get_qsb_data_2($category_id = '', $subject_id = '', $level_id = ''){	
	
	get_qsb_data_load($category_id, $subject_id, $level_id, $question_level='2', $first_qq = 'category');
}

function get_qsb_data_3_c($category_id = '', $subject_id = '', $level_id = ''){	
    
    get_qsb_data_load($category_id, $subject_id, $level_id, $question_level='3', $first_qq = 'category');
}
function call_is_service($fields){	
	
	$type_id = "1";
	
	//$fields['type'] = explode(",", $type_id); // degree type = 1	in IS
    
    //[version 2]remove Campus Type for only GS to fix 66161, eLearners and EMD still need it
    $fields['campus_type'] = array('0'=>1);
    
    if($fields['first_qq'] == 'level')
        return call_is_service_level_first($fields);
    else
        return call_is_service_category_first($fields);
	
}


//function call_drupal($fields){	

//    if($fields['qq_level'] == '3'){
//        if(empty($fields['level'])){
		
//            return get_taxonomy_terms_from_drupal('levels');	
			
//        }elseif(empty($fields['category'])){
		
//            return get_taxonomy_terms_from_drupal('categories');
			
//        }else{
		
//            return get_taxonomy_terms_from_drupal('subjects');
			
//        }
//    }else{
//        if(empty($fields['category'])){
			
//            return get_taxonomy_terms_from_drupal('categories');	
			
//        }else{
		
//            return get_taxonomy_terms_from_drupal('subjects');
			
//        }
//    }
//}


function get_sort($fields){	

	if($fields['qq_level'] == '3'){
		if(empty($fields['level'])){
		
			return 'sort_by_showvalue';	
			
		}elseif(empty($fields['category'])){
		
			return 'sort_by_title';	
			
		}else{
		
			return 'sort_by_title';
			
		}
	}else{
		
		return 'sort_by_title';
	}
}

//function get_iss_data($fields){
	
//    if($fields['qq_level'] == '3'){
//        if(empty($fields['level'])){
		
//            return "ProgramLevelId"; //get_iss_field('levels');	
			
//        }elseif(empty($fields['category'])){
		
//            return "CategoryId"; //get_iss_field('categories');	
			
//        }else{
		
//            return "SubjectId"; //get_iss_field('subjects');
			
//        }
		
//    }else{
	
//        if(empty($fields['category'])){
		
//            return "CategoryId"; //get_iss_field('categories');	
			
//        }else{
		
//            return "SubjectId"; //get_iss_field('subjects');
			
//        }

//    }
//}

//function get_alias_url($fields, $tid, $term_type){

//    if($fields['qq_level'] == '3'){
//        if(!empty($fields['level'])){							

			
//            return get_node_alias_by_terms($fields, $tid, $term_type);								
		
//        }else{
		
//            return "";
		
//        }
//    }else{
	
//        if(!empty($fields['category'])){							

			
//            return get_node_alias_by_terms($fields, $tid, $term_type);								
		
//        }else{
		
//            return "";
		
//        }
//    }
//}


// not using in emd
function get_campus_type(){
	
	//1334--campus, 1335--online,
	return '1335';
}

// not using in elearners
//function get_degree_type_tid($degree_type = ''){

//    if(empty($degree_type)){
	
//        return array(4); // degree type tid=4
		
//    }
//}
	

//function get_node_alias_by_terms($fields, $tid, $term_type){
	
//    if($fields['qq_level'] == '3'){
//        $ask_alias_url = get_node_alias_level_first($fields, $tid, $term_type);
//    }else{
//        $ask_alias_url = get_node_alias_category_first($fields, $tid, $term_type);
//    }
//    return $ask_alias_url;
	
//}	
	
