<?php require_once('shared.php');

   

$action = isset($_POST['action']) ? $_POST['action'] : '' ; 
$isfilter = isset($_POST['isfilter']) ? $_POST['isfilter'] : 0 ;
$ispaging = isset($_POST['ispaging']) ? $_POST['ispaging'] : 0 ;
$istbclick = isset($_POST['istbclick']) ? $_POST['istbclick'] : 0 ;
$isview = isset($_POST['isview']) ? $_POST['isview'] : 0 ;
$issave = isset($_POST['issave']) ? $_POST['issave'] : 0 ;
$isdelete = isset($_POST['isdelete']) ? $_POST['isdelete'] : 0 ;
$isupdate = isset($_POST['isupdate']) ? $_POST['isupdate'] : 0 ;
$isedit = isset($_POST['isedit']) ? $_POST['isedit'] : 0 ;
$isclear = isset($_POST['isclear']) ? $_POST['isclear'] : 0 ;
$istmbhrw = isset($_POST['istmbhrw']) ? $_POST['istmbhrw'] : 0 ;
$isgetkki = isset($_POST['isgetkki']) ? $_POST['isgetkki'] : 0 ;
$iskkiexist = isset($_POST['iskkiexist']) ? $_POST['iskkiexist'] : 0 ;
$isgetkak = isset($_POST['isgetkak']) ? $_POST['isgetkak'] : 0 ;
$iskakexist = isset($_POST['iskakexist']) ? $_POST['iskakexist'] : 0 ;

$nm_menu = isset($_POST['nm_menu']) ? $_POST['nm_menu'] : '' ; 
$menu_idx = isset($_POST['menu_idx']) ? $_POST['menu_idx'] : -1 ;
$menu_idx1 = isset($_POST['menu_idx1']) ? $_POST['menu_idx1'] : -1 ;
$menu_idx2 = isset($_POST['menu_idx2']) ? $_POST['menu_idx2'] : -1 ;
$menu_idx3 = isset($_POST['menu_idx3']) ? $_POST['menu_idx3'] : -1 ;

$idkec = isset($_POST['idkec']) ? $_POST['idkec'] : 0 ; 
$iddesa = isset($_POST['iddesa']) ? $_POST['iddesa'] : 0 ;       
$iddusun = isset($_POST['iddusun']) ? $_POST['iddusun'] : 0 ;    
$idrt = isset($_POST['idrt']) ? $_POST['idrt'] : 0 ; 

//$id_pra_s = isset($_POST['id_1']) ? $_POST['id_1'] : array() ;
//$id_ks_1 = isset($_POST['id_2']) ? $_POST['id_2'] : array() ;
//$id_ks_2 = isset($_POST['id_3']) ? $_POST['id_3'] : array() ;
//$id_ks_3 = isset($_POST['id_4']) ? $_POST['id_4'] : array() ;
//$id_ks_3_p = isset($_POST['id_5']) ? $_POST['id_5'] : array() ;

switch($action)
{
   case 'menu' : switch($menu_idx)
                 {
                    case 0 :switch($menu_idx1)
                             {
                                case 0 : echo $nm_menu; break;
                                case 1 : 
                                        $vw=new vw_setup;                                        
                                        if($issave==1){                                           
                                           $id_pra_s = isset($_POST['id_1']) ? $_POST['id_1'] : array() ;
                                           $id_ks_1 = isset($_POST['id_2']) ? $_POST['id_2'] : array() ;
                                           $id_ks_2 = isset($_POST['id_3']) ? $_POST['id_3'] : array() ;
                                           $id_ks_3 = isset($_POST['id_4']) ? $_POST['id_4'] : array() ;
                                           $id_ks_3_p = isset($_POST['id_5']) ? $_POST['id_5'] : array() ;

                                           echo $vw->save_ind_ks($id_pra_s,$id_ks_1,$id_ks_2,$id_ks_3,$id_ks_3_p);
                                        }elseif($isclear==1){
                                           echo $vw->clear_ind_ks();
                                        
                                        }else{                                           
                                           echo $nm_menu.'<br>'.$vw->menu02_hslfilter();
                                         }  
                                         break;
                                case 2 : echo $nm_menu;break;
                                case 3 : echo $nm_menu;break;
                                case 4 : $vw=new vw_setup;
                                         
                                              echo $nm_menu.'<br>'.$vw->menu04_view();
                                            
                                         break;                                
                             }
                            break;
                    case 1 : switch($menu_idx1)
                             {
                                case 0 : $vw=new vw_data;
                                         
                                         
                                         if($iskkiexist==1)
                                         {
                                            $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                            echo $vw->kki_exist($kki);
                                         }elseif ($iskakexist==1) {
                                            $kak = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            echo $vw->kak_exist($kak);
                                         }elseif($issave==1){
                                            $fam = isset($_POST['fam']) ? $_POST['fam'] : array() ;
                                            $indv = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            $ind_ks = isset($_POST['ind_ks']) ? $_POST['ind_ks'] : array() ;
                                            echo $vw->insert_data($fam,$indv,$ind_ks);
                                         }elseif($isgetkki==1){
                                              echo $vw->get_kki($iddesa);
                                         }elseif($isgetkak==1)
                                         {
                                            echo $vw->get_kak($iddesa); 
                                         }elseif($istmbhrw==1){
                                               $jmlbrs=isset($_POST['jmlbrs']) ? $_POST['jmlbrs'] : 0; 
                                               echo $vw->tambah_row($jmlbrs);
                                         }else{
                                                     echo $nm_menu."<br><div id='data'>".$vw->tambah_data().'</div>';                                                
                                              }
                                         break;
                                case 1 : $vw=new vw_data;
                                         
                                         if($iskkiexist==1)
                                         {
                                            $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                            echo $vw->kki_exist($kki);
                                         }elseif ($iskakexist==1) {
                                            $kak = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            echo $vw->kak_exist($kak);
                                         }elseif($isgetkki==1){
                                              echo $vw->get_kki($iddesa);
                                         }elseif($isgetkak==1)
                                         {
                                            echo $vw->get_kak($iddesa); 
                                         }elseif($istmbhrw==1){
                                               $jmlbrs=isset($_POST['jmlbrs']) ? $_POST['jmlbrs'] : 0; 
                                               echo $vw->tambah_row($jmlbrs);
                                         }elseif($isupdate==1)
                                         {
                                            $fam = isset($_POST['fam']) ? $_POST['fam'] : array() ;
                                            $indv = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            $ind_ks = isset($_POST['ind_ks']) ? $_POST['ind_ks'] : array() ;
                                            echo $vw->update_data($fam,$indv,$ind_ks);
                                         }
                                         elseif($isfilter==0){
                                           echo $nm_menu.'<br>'.$vw->menu_filter();
                                         }else
                                            {
                                              $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                              echo $nm_menu.'<br>'.$vw->view_form_update($kki);;  
                                            }                                         
                                         break;
                                case 2 : $vw=new vw_data;
                                         if($isdelete==1)
                                         {
                                           $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                           echo $vw->db_hapus_data($kki);
                                         }elseif($isfilter==0){
                                           echo $nm_menu.'<br>'.$vw->menu_filter();
                                         }else
                                            {
                                              $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                              echo $nm_menu.'<br>'.$vw->hapus_data($kki);  
                                            }
                                         break;
                                case 3 : $vw=new vw_data;
                                         
										if($ispaging==1)
                                        {
                                          echo json_encode($vw->ss_viewdata($_POST));  
                                        }elseif($istmbhrw==1){
                                               $jmlbrs=isset($_POST['jmlbrs']) ? $_POST['jmlbrs'] : 0; 
                                               echo $vw->tambah_row($jmlbrs);
                                         }elseif($isupdate==1)
                                         {
                                            $fam = isset($_POST['fam']) ? $_POST['fam'] : array() ;
                                            $indv = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            $ind_ks = isset($_POST['ind_ks']) ? $_POST['ind_ks'] : array() ;
                                            echo $vw->edit_data($fam,$indv,$ind_ks);
                                         }elseif($isedit==1)
                                         {
                                           $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                           echo $vw->edt_edit_data($kki);
                                         }elseif($iskkiexist==1)
                                         {
                                            $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                            echo $vw->kki_exist($kki);
                                         }elseif ($iskakexist==1) {
                                            $kak = isset($_POST['indv']) ? $_POST['indv'] : array() ;
                                            echo $vw->kak_exist($kak);
                                         }elseif($isview==1)
                                         {
                                           $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                           echo $vw->edt_view_data($kki);
                                         }elseif($isdelete==1)
                                         {
                                           $kki = isset($_POST['kki']) ? $_POST['kki'] : '';
                                           echo $vw->edit_hapus_data($idkec,$iddesa,$iddusun,$idrt,$kki);
                                         }elseif($isfilter==0){  
                                               echo $nm_menu.'<br>'.$vw->menu_filter1();
                                          }else
                                          {
                                             echo $nm_menu.'<br>'.$vw->tb_edt_data($idkec,$iddesa,$iddusun,$idrt);
                                          }
                                         break;
                                case 4 : echo $nm_menu;break;                                
                             }
                             break;
                    case 2 : switch($menu_idx1)
                             {
                                case 0 : switch($menu_idx2)
                                         {
                                            case 0 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu01_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;
                                            case 1 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;
                                            case 2 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;
                                            case 3 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu04_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;
                                            case 4 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu05_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 5 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu06_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 6 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu07_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 7 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu08_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 8 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu09_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 9 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu010_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 10 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu011_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;  
                                            case 11 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu012_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;   
                                            case 12 :$vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu013_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;    
                                            case 13 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu014_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;   
                                            case 14 :  $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu015_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 15 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu016_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 16 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu017_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break; 
                                            case 17 : $vw=new vw_tbkependudukan;
                                                     if($isfilter==0){  
                                                       echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                         {
                                                            echo $nm_menu.'<br>'.$vw->menu018_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                         }
                                                     break;                                
                                         }
                                         break;
                                case 1 : switch($menu_idx2)
                                         {
                                            case 0 : switch($menu_idx3)
                                                     {
                                                        case 0 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu101_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 1 :  $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu102_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 2 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu103_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 3 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu104_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 4 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu105_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 5 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu106_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 6 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu107_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;                                  
                                                     }
                                                     break;
                                            case 1 : switch($menu_idx3)
                                                     {
                                                        case 0 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu111_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break; 
                                                        case 1 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu112_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;
                                                        case 2 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu113_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;
                                                        case 3 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu114_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;
                                                        case 4 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu115_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;
                                                        case 5 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter();
                                                                 }else
                                                                     {
                                                                        echo $nm_menu.'<br>'.$vw->menu116_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                                     }
                                                                 break;
                                                                                   
                                                     }
                                                     break;                                                                                            
                                         }
                                         break;
                                case 2 : switch($menu_idx2)
                                         {
                                            case 0 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0),array('ks'=>1));
                                                                 }else
                                                                     {
                                                                        $cmbks = isset($_POST['cmbks']) ? $_POST['cmbks'] : '' ; 
                                                                        echo $nm_menu.'<br>'.$vw->menu21_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbks);
                                                                     }
                                                                 break;
                                            case 1 : $vw=new vw_tbkependudukan;
                                                                 if($isfilter==0){  
                                                                   echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0),array('ks'=>1,'umur'=>1,'edu'=>1));
                                                                 }else
                                                                     {
                                                                        $cmbks = isset($_POST['cmbks']) ? $_POST['cmbks'] : '' ;
                                                                        $cmbumur = isset($_POST['cmbumur']) ? $_POST['cmbumur'] : '' ;
                                                                        $data[] = isset($_POST['data1']) ? $_POST['data1'] : 0 ;
                                                                        $data[] = isset($_POST['data2']) ? $_POST['data2'] : 0 ;

                                                                        $edu = isset($_POST['edu']) ? $_POST['edu'] : array();

                                                                        echo $nm_menu.'<br>'.$vw->menu22_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbks,$cmbumur,$data,$edu);
                                                                     }
                                                                 break;                                                                                            
                                         }
                                         break;
                                case 3 : $vw=new vw_tbkependudukan;
                                         if($isfilter==0){  
                                             echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0),array('ks'=>1));
                                         }else
                                         {
                                             $cmbks = isset($_POST['cmbks']) ? $_POST['cmbks'] : '' ; 
                                             echo $nm_menu.'<br>'.$vw->menu3_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbks);
                                         }
                                         break;
                                case 4 : $vw=new vw_tbkependudukan;
                                         if($isfilter==0){  
                                             echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                         }else
                                         {
                                             echo $nm_menu.'<br>'.$vw->menu4_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                         }
                                         break; 
                                case 5 : $vw=new vw_tbkependudukan;
                                         if($isfilter==0){  
                                             echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                         }else
                                         {
                                             echo $nm_menu.'<br>'.$vw->menu5_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                         }
                                         break;                                
                             }
                             break;
                    case 3 : switch($menu_idx1)
                             {
                                case 0 :$vw=new vw_report;
                                        if($ispaging==1)
                                        {
                                          echo json_encode($vw->menu01_ss_viewdata($_POST));  
                                        }elseif($isfilter==0){  
                                            echo $nm_menu.'<br>'.$vw->menu_filter();
                                        }else
                                        {
                                            echo $nm_menu.'<br>'.$vw->menu01_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                        }
                                        break;
                                case 1 : $vw=new vw_report;
                                        if($istbclick==1)
                                        {
                                            $tbidx = isset($_POST['tbidx']) ? $_POST['tbidx'] : 0;
                                            switch($tbidx)
                                            {
                                              case 1 : echo $vw->menu02_tab1_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 2 : echo $vw->menu02_tab2_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 3 : echo $vw->menu02_tab3_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 4 : echo $vw->menu02_tab4_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 5 : echo $vw->menu02_tab5_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break; 
                                            }

                                        }elseif($isfilter==0){  
                                            echo $nm_menu.'<br>'.$vw->menu_filter(array(),array(),array('kec'=>0,'desa'=>0));
                                        }else
                                        {
                                            echo $nm_menu.'<br>'.$vw->menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                        }
                                        break;
                                case 2 :  $vw=new vw_report;
                                        if($istbclick==1)
                                        {
                                            $tbidx = isset($_POST['tbidx']) ? $_POST['tbidx'] : 0;
                                            switch($tbidx)
                                            {
                                              case 1 : echo $vw->menu03_tab1_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 2 : echo $vw->menu03_tab2_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 3 : echo $vw->menu03_tab3_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 4 : echo $vw->menu03_tab4_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 5 : echo $vw->menu03_tab5_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break; 
                                              case 6 : echo $vw->menu03_tab6_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 7 : echo $vw->menu03_tab7_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 8 : echo $vw->menu03_tab8_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 9 : echo $vw->menu03_tab9_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;
                                              case 10 : echo $vw->menu03_tab10_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break; 
                                              case 11 : echo $vw->menu03_tab11_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                       break;

                                            }

                                        }elseif($isfilter==0){  
                                            echo $nm_menu.'<br>'.$vw->menu_filter(array('rt'=>0));
                                        }else
                                        {
                                            echo $nm_menu.'<br>'.$vw->menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                        }
                                        break;                                                    
                             }
                             break;
                    case 4 : switch($menu_idx1)
                             {
                                case 0 : switch($menu_idx2)
                                         {
                                            case 0 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                     {
                                                         echo $nm_menu.'<br>'.$vw->menu401_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                     }
                                                     break;   
                                            case 1 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                     {
                                                         echo $nm_menu.'<br>'.$vw->menu402_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                     }
                                                     break;  
                                            case 2 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter(array(),array('kb'=>1));
                                                     }else
                                                     {   $cmbkb = isset($_POST['cmbkb']) ? $_POST['cmbkb'] : '' ;
                                                         echo $nm_menu.'<br>'.$vw->menu403_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbkb);
                                                     }
                                                     break;
                                            case 3 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter(array(),array('kb1'=>1,'ks1'=>1));
                                                     }else
                                                     {   $cmbkb = isset($_POST['cmbkb1']) ? $_POST['cmbkb1'] : '' ;
                                                         $cmbks = isset($_POST['cmbks1']) ? $_POST['cmbks1'] : '' ;
                                                         echo $nm_menu.'<br>'.$vw->menu404_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbkb,$cmbks);
                                                     }
                                                     break;                             
                                         }
                                        break;
                                case 1 : switch($menu_idx2)
                                         {
                                            case 0 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                     {
                                                         echo $nm_menu.'<br>'.$vw->menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                     }
                                                     break;                          
                                         }
                                        break;
                                case 2 : switch($menu_idx2)
                                         {
                                            case 0 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter();
                                                     }else
                                                     {
                                                         echo $nm_menu.'<br>'.$vw->menu421_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                                     }
                                                     break;
                                            case 1 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter(array(),array('umur'=>1));
                                                     }else
                                                     {
                                                         $cmbumur = isset($_POST['cmbumur']) ? $_POST['cmbumur'] : '' ;
                                                         $data[] = isset($_POST['data1']) ? $_POST['data1'] : 0 ;
                                                                        $data[] = isset($_POST['data2']) ? $_POST['data2'] : 0 ;
                                                         echo $nm_menu.'<br>'.$vw->menu422_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$data);
                                                     }
                                                     break;
                                            case 2 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter(array(),array('umur'=>1,'kerja'=>1));
                                                     }else
                                                     {
                                                         $cmbumur = isset($_POST['cmbumur']) ? $_POST['cmbumur'] : '' ;
                                                         $data[] = isset($_POST['data1']) ? $_POST['data1'] : 0 ;
                                                                        $data[] = isset($_POST['data2']) ? $_POST['data2'] : 0 ;
                                                         $cmbkerja = isset($_POST['cmbkerja']) ? $_POST['cmbkerja'] : '' ;
                                                         echo $nm_menu.'<br>'.$vw->menu423_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$data,$cmbkerja);
                                                     }
                                                     break;
                                            case 3 : $vw=new vw_rekapitulasi;
                                                     if($isfilter==0){  
                                                         echo $nm_menu.'<br>'.$vw->menu_filter(array(),array('sekolah'=>1));
                                                     }else
                                                     {
                                                         $cmbsekolah = isset($_POST['cmbsekolah']) ? $_POST['cmbsekolah'] : '' ;
                                                         echo $nm_menu.'<br>'.$vw->menu424_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbsekolah);
                                                     }
                                                     break;                              
                                         }
                                        break;
                                case 3 : $vw=new vw_rekapitulasi;
                                         if($isfilter==0){  
                                          echo $nm_menu.'<br>'.$vw->menu_filter();
                                         }else
                                         {
                                          echo $nm_menu.'<br>'.$vw->menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                         }
                                         break;
                                case 4 : $vw=new vw_rekapitulasi;
                                         if($isfilter==0){  
                                          echo $nm_menu.'<br>'.$vw->menu_filter();
                                         }else
                                         {
                                          echo $nm_menu.'<br>'.$vw->menu04_hslfilter($idkec,$iddesa,$iddusun,$idrt);
                                         }
                                         break;                               
                             }
                             break;
                    case 5 : switch($menu_idx1)
                             {
                                case 0 : echo $nm_menu;break;
                                case 1 : echo $nm_menu;break;
                                case 2 : switch($menu_idx2)
                                         {
                                            case 0 : echo $nm_menu; break;
                                            case 1 : echo $nm_menu;break;
                                            case 2 : echo $nm_menu;break;                              
                                         }
                                        break;
                                case 3 : echo $nm_menu;break;
                                case 4 : echo $nm_menu;break;                              
                             }
                             break;
                    case 6 : break;
                 }                     
                 break;
}

   $pra = isset($_POST['pra']) ? $_POST['pra'] : array() ;
   $ks = isset($_POST['ks']) ? $_POST['ks'] : array() ;
   $ks1 = isset($_POST['ks1']) ? $_POST['ks1'] : array() ;

   
   $idx = isset($_POST['idx']) ? $_POST['idx'] : '' ; 

   $dtunit = new dt_unit_detail;
      
   switch($idx)
   {
      case 1 : $vw = new vw_index;
               $tmp = 'KECAMATAN : '.$dtunit->getnm("id_unit_detail='$idkec'");
               //echo $vw->hsl_filter($pra,$ks,$ks1,$tmp,$idx,$idkec);
               break;
      case 2 : 
               break;
      case 3 : $vw = new vw_index;                 
                $tmp = 'KECAMATAN : '.$dtunit->getnm("id_unit_detail='$idkec'").'   DESA : '.$dtunit->getnm("id_unit_detail='$iddesa'");
                //echo $vw->hsl_filter($pra,$ks,$ks1,$tmp,$idx,$iddesa,$idkec);
               break;
      case 4 : 
               break;
      case 5 : $vw = new vw_index;
               $tmp = 'KECAMATAN : '.$dtunit->getnm("id_unit_detail='$idkec'").'    DESA : '.$dtunit->getnm("id_unit_detail='$iddesa'").'    RW : '.$dtunit->getnm("id_unit_detail='$iddusun'");
               //echo $vw->hsl_filter($pra,$ks,$ks1,$tmp,$idx,$iddusun,$iddesa);
               break;
      case 6 : 
               break;
      case 7 : $unit = new dt_unit_detail;
               $mycmb=new mycmb;

               $first = isset($_POST['firstdesa']) ? $_POST['firstdesa'] : '';  
               if(empty($first)){ 
                 echo $mycmb->cmb_desa($unit->getdesa($idkec));
               }else{
                echo $mycmb->cmb_desa($unit->getdesa($idkec),$first);
               }  
               break;
      case 8 : $unit = new dt_unit_detail;
               $mycmb=new mycmb;
                $first = isset($_POST['firstdusun']) ? $_POST['firstdusun'] : '';  
               if(empty($first)){ 
                 echo $mycmb->cmb_dusun($unit->getdusun($iddesa));
               }else{
                 echo $mycmb->cmb_dusun($unit->getdusun($iddesa),$first); 
               }
               break;
      case 9 : $unit = new dt_unit_detail;
               $mycmb=new mycmb;
                $first = isset($_POST['firstrt']) ? $_POST['firstrt'] : '';  
                if(empty($first)){ 
                 echo $mycmb->cmb_rt($unit->getRT($iddusun));
                }else{
                 echo $mycmb->cmb_rt($unit->getRT($iddusun),$first);   
                } 
               break;

                                            
   }

?>