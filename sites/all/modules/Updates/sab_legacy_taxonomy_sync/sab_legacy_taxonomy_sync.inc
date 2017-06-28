<?php

//function sab_legacy_taxonomy_sync_legacy_endeca_to_category_terms() {
//    if (($handle = fopen($_SERVER['APPL_PHYSICAL_PATH'] . drupal_get_path('module', 'sab_legacy_taxonomy_sync') . "/data/Categories.csv", "r")) !== FALSE) {
//        //Remove First Line from CSV:
//        fgetcsv($handle, 1000, ",");
        
//        //Adds Everything else except the first line.
//        $totalTerms = 0;
//        $totalTermsFound = 0;
        
//        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
//            $totalTerms++;
//            $createterm=  sab_legacy_taxonomy_sync_create_term($data,8); // create terem
//            $updated_term = sab_legacy_taxonomy_sync_update_term($data,8); //update term: 8=Catergies
//            if(!is_null($updated_term)){
//                $totalTermsFound++;
//                taxonomy_term_save($updated_term);
//            }
//        }
//        fclose($handle);
//    } 

//}


//function taxonomy_get_term_by_name($name, $vocabulary = NULL) {
//    $conditions = array('name' => trim($name));
//    if (isset($vocabulary)) {
//        $vocabularies = taxonomy_vocabulary_get_names();
//        if (isset($vocabularies[$vocabulary])) {
//            $conditions['vid'] = $vocabularies[$vocabulary]->vid;
//        }
//        else {
//            // Return an empty array when filtering by a non-existing vocabulary.
//            return array();
//        }
//    }
//    return taxonomy_term_load_multiple(array(), $conditions);
//}

//Check for subjects then specialties
function sab_legacy_taxonomy_sync_legacy_endeca_to_subject_terms() {
    if (($handle = fopen($_SERVER['APPL_PHYSICAL_PATH'] . drupal_get_path('module', 'sab_legacy_taxonomy_sync') . "/data/Subjects.csv", "r")) !== FALSE) {
        //Remove First Line from CSV:
        fgetcsv($handle, 1000, ",");
        $totalTerms = 0;
        $totalTermsFound = 0;
        ////Adds Everything else except the first line.
        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {

            $createterm=  sab_legacy_taxonomy_sync_create_term($data,5); // create terem
            $updated_term = sab_legacy_taxonomy_sync_update_term($data,5);
            $totalTerms++;
            if(!is_null($updated_term)){
                $totalTermsFound++;
                taxonomy_term_save($updated_term);
            }else
            {
                //$updated_term = sab_legacy_taxonomy_sync_update_term($data,11);
                //if(!is_null($updated_term)){
                //    $totalTermsFound++;
                //    taxonomy_term_save($updated_term);
                //}
            }
        }
        fclose($handle);
        //dpm($totalTerms);
        //dpm($totalTermsFound);
    } 
}

//function gs_legacy_taxonomy_sync_legacy_endeca_to_specialty_terms() {
//    if (($handle = fopen($_SERVER['APPL_PHYSICAL_PATH'] . drupal_get_path('module', 'gs_legacy_taxonomy_sync') . "/data/Specialties.csv", "r")) !== FALSE) {
//        //Remove First Line from CSV:
//        fgetcsv($handle, 1000, ",");
//        $totalTerms = 0;
//        $totalTermsFound = 0;
//        ////Adds Everything else except the first line.
//        while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
//            $totalTerms++;
//            $updated_term = gs_legacy_taxonomy_sync_update_term($data,11);
//            if(!is_null($updated_term)){
//                $totalTermsFound++;
//                taxonomy_term_save($updated_term);
//            }else{
//                $updated_term = gs_legacy_taxonomy_sync_update_term($data,5);
//                if(!is_null($updated_term)){
//                    $totalTermsFound++;
//                    taxonomy_term_save($updated_term);
//                }
//            }
//        }
//        fclose($handle);
//        dpm($totalTerms);
//        dpm($totalTermsFound);
//    } 
//}

