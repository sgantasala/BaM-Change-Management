<?php
module_load_include('inc', 'eddy_qsb', 'service-include/eddy_qsb_service');

function get_qsb_data($level_id = '', $category_id = '', $subject_id = ''){	
    
	get_qsb_data_load($category_id, $subject_id, $level_id);
}	

function get_qsb_data_2($category_id = '', $subject_id = '', $level_id = ''){	
	
    $level_id = "7,8,11";
    
	get_qsb_data_load($category_id, $subject_id, $level_id, $question_level='2', $first_qq = 'category');
}

function get_qsb_data_3_c($category_id = '', $subject_id = '', $level_id = ''){	
    
    $level_id = "7,8,11";

    get_qsb_data_load($category_id, $subject_id, $level_id, $question_level='3', $first_qq = 'category');
}

function call_is_service($fields){	
	
	//remove ProgramTypeList to fix 66161
    //$type_id = "1";
	
	//$fields['type'] = explode(",", $type_id); // degree type = 1	in IS
    
	if($fields['first_qq'] == 'level')
        return call_is_service_level_first($fields);
    else
        return call_is_service_category_first($fields);
}

function get_sort($fields){	

    if($fields['first_qq'] == 'level'){

		if(empty($fields['level'])){
            
			return 'sort_by_showvalue';	
			
		}elseif(empty($fields['category'])){
            
			return 'sort_by_title';
			
		}elseif($fields['qq_level'] == '3'){
			return 'sort_by_title';            
		}
    }else{        
		
        if(empty($fields['category'])){
            
            return 'sort_by_title';	
            
        }elseif(empty($fields['subject'])){
            
            return 'sort_by_title';
            
        }elseif($fields['qq_level'] == '3'){
                return 'sort_by_showvalue';            
        }
	}
}


//function get_certificate_level_tid(){

//    return 3;//certificate tid as level

//}
//function get_iss_data($fields){
//    if($fields['first_qq'] == 'level'){
	
//        if(empty($fields['level'])){
		
//            return "ProgramLevelId"; //get_iss_field('levels');	
			
//        }elseif(empty($fields['category'])){
		
//            return "CategoryId"; //get_iss_field('categories');	
			
//        }elseif($fields['qq_level'] == '3'){
		
//            return "SubjectId"; //get_iss_field('subjects');
			
//        }
		
//    }else{
	
//        if(empty($fields['category'])){
		
//            return "CategoryId"; //get_iss_field('categories');	
			
//        }elseif(empty($fields['subject'])){
		
//            return "SubjectId"; //get_iss_field('subjects');
			
//        }elseif($fields['qq_level'] == '3'){
//            return "ProgramLevelId"; //get_iss_field('levels');	
//        }
//    }
//}

//function get_alias_url($fields, $tid, $term_type){

//    if($fields['first_qq'] == 'level'){
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




//function get_node_alias_by_terms($fields, $tid, $term_type){
	
//    if($fields['first_qq'] == 'level'){
//        $ask_alias_url = get_node_alias_level_first($fields, $tid, $term_type);
//    }else{
//        $ask_alias_url = get_node_alias_category_first($fields, $tid, $term_type);
//    }
//    return $ask_alias_url;
	
//}	
	
