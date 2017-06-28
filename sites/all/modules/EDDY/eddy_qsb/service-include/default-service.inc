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


function get_certificate_level_tid(){

	return 3;//certificate tid as level

}
