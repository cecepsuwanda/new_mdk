<?php require_once('shared.php');
     
class vw_rekapitulasi
{
   function __construct() {
		
   }

   function menu_filter($hide=array(),$show=array()){
   	 $frmfilter = new frm_filter;
   	 $html_txt = $frmfilter->cmb_filter($hide,$show)."<br><br>";
   	 $html_txt .= "<div id='data'>";
   	 $html_txt .= "</div>";
   	 return $html_txt; 
   }

   private function getnmklm($idkec,$iddesa,$iddusun,$idrt)
   {
        $nmklm='KECAMATAN';
        $nmklm= $idkec ? 'DESA/KELURAHAN' : $nmklm;
        $nmklm= $iddesa ? 'DUSUN/RW' : $nmklm;
        $nmklm= $iddusun ? 'RT' : $nmklm;      
        
        return $nmklm;    
   }

   private function getsubjudul($idkec,$iddesa,$iddusun,$idrt)
   {
         $dtunit = new dt_unit_detail;         
         $subjudul='KAB/KOTA :KABUPATEN BANDUNG BARAT ';         
         $subjudul .= ($idkec>0) ? ' >> KECAMATAN : '.$dtunit->getnm("id_unit_detail='$idkec'") : '';        
         $subjudul .= ($iddesa>0) ? ' >> DESA : '.$dtunit->getnm("id_unit_detail='$iddesa'") : '';
         $subjudul .= ($iddusun>0) ? ' >> RW : '.$dtunit->getnm("id_unit_detail='$iddusun'") : '';   
         $subjudul .= ($idrt>0) ? ' >> RT : '.$dtunit->getnm("id_unit_detail='$idrt'") : '';         

       return $subjudul;  
   }

   private function build_dt_tb($tmp_dt_tb,$jdl_baris=array('JUMLAH'))
   {
       $dt_tb=array();
       $txt='';
       if(!empty($tmp_dt_tb))
       {
         
          foreach($tmp_dt_tb['isi_tb'] as $row)
          {
             $tmp=array();
            foreach ($row as $key => $value) {
               $tmp[]=array($value,array('align'=>'center'));            
            } 
             $dt_tb[]=$tmp;
          }
             
           $txt = ''; 
           $i=0;          
          foreach ($jdl_baris as $row) {
                $txt = $txt."<tr>";            
                $txt = $txt."<th colspan='2'>$row</th>";                      
                $jml1 = count($tmp_dt_tb['footer_tb']);
                $jml2 = count($tmp_dt_tb['footer_tb'],1);
                if($jml1==$jml2){
                   foreach($tmp_dt_tb['footer_tb'] as $row)
                   {
                     $txt = $txt."<th align='right'>".$row."</th>";
                   }
                }else{
                    foreach($tmp_dt_tb['footer_tb'][$i] as $row)
                    {
                      $txt = $txt."<th align='right'>".$row."</th>";
                    }
                    $i++;
                  }
                 $txt = $txt."</tr>";
                }
          }
       

       return array('dt_tb'=>$dt_tb,'footer_tb'=>$txt);
   }

   function menu401_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>TAHAPAN PRA S DAN KS I</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu401($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('JUMLAH JIWA',array('rowspan'=>'2')),
                                               array('TAHAPAN KS',array('colspan'=>'2'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA',array('rowspan'=>'2')),
                        array('TAHAPAN KS',array('colspan'=>'2'))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       array(array('PRA S',array()),array('KS I',array()))
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   } 

   function menu402_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>TAHAPAN PRA S DAN KS I ALEK & NON ALEK</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu402($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'3')),
                                               array($nmklm,array('rowspan'=>'3')),
                                               array('JUMLAH KK',array('rowspan'=>'3')),
                                               array('JUMLAH JIWA',array('rowspan'=>'3')),
                                               array('TAHAPAN KS',array('colspan'=>'4'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'3')),
                        array('KEPALA KELUARGA',array('rowspan'=>'3')),
                        array('JUMLAH JIWA',array('rowspan'=>'3')),
                        array('TAHAPAN KS',array('colspan'=>'4'))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       array(array('PRA S',array('colspan'=>'2')),array('KS I',array('colspan'=>'2'))),
                       array(array('ALEK',array()),array('NON ALEK',array()),array('ALEK',array()),array('NON ALEK',array()))
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   } 

   function menu403_hslfilter($idkec,$iddesa,$iddusun,$idrt,$kb){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'PUS ' : 'DAFTAR KELUARGA ').($kb==1 ? "KB" : "NON KB").", PRA S DAN KS I</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu403($idkec,$iddesa,$iddusun,$idrt,$kb);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('JUMLAH JIWA',array('rowspan'=>'2')),
                                               array('TAHAPAN KS',array('colspan'=>'2'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA',array('rowspan'=>'2')),
                        array('TAHAPAN KS',array('colspan'=>'2'))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       array(array('PRA S',array()),array('KS I',array()))
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   } 

   function menu404_hslfilter($idkec,$iddesa,$iddusun,$idrt,$kb,$ks){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu404($idkec,$iddesa,$iddusun,$idrt,$kb,$ks);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 
       
       if($kb==1){
          $dt_contr = new dt_contr_typ;
          $nmcontyp = $dt_contr->getnm('',empty($idrt) ? 1:0,0,0);
          $numrows=$dt_contr->getnumrows();        
             if($ks==2)
             {
               $nmcontyp = $dt_contr->getnm('',empty($idrt) ? 1:0,0,0,$nmcontyp);  
             }
      }            


       if(empty($idrt)){
          switch($ks)
          {
            case 1 : switch($kb)
                     {
                       case 1 :   $html_txt = "<center><bold>PUS & KB</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                                      array($nmklm,array('rowspan'=>'2')),
                                                      array('JUMLAH KK',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PESERTA KB',array('colspan'=>$numrows+1))
                                                     ),                                          
                                                 $nmcontyp
                                                );


                                break;
                       case 2 : $html_txt = "<center><bold>NON KB</bold><br>$subjudul</center>";
                                $jdl_tb = array(array(array('NO. KODE',array()),
                                                      array($nmklm,array()),
                                                      array('JUMLAH KK',array()),
                                                      array('JUMLAH JIWA',array()),
                                                      array('JUMLAH PUS',array())
                                                     )
                                                );


                                break;
                       case 3 : $html_txt = "<center><bold>KB & NON KB</bold><br>$subjudul</center>";
                                $jdl_tb = array(array(array('NO. KODE',array()),
                                                      array($nmklm,array()),
                                                      array('JUMLAH KK',array()),
                                                      array('JUMLAH JIWA',array()),
                                                      array('JUMLAH PUS',array()),
                                                      array('KB',array()),
                                                      array('NON KB',array())
                                                     )
                                                );


                                break;
                     }
                     break;
            case 2 : switch($kb)
                     {
                       case 1 :   $html_txt = "<center><bold>PUS, KB PRA S & KS I</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                                      array($nmklm,array('rowspan'=>'2')),
                                                      array('JUMLAH KK',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PRA S',array('colspan'=>$numrows+1)),
                                                      array('KS I',array('colspan'=>$numrows+1))
                                                     ),                                          
                                                 $nmcontyp
                                                );

                                break;
                       case 2 : $html_txt = "<center><bold>PUS NON KB,PRA S DAN KS I</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                                      array($nmklm,array('rowspan'=>'2')),
                                                      array('JUMLAH KK',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('TAHAPAN KS',array('colspan'=>'2'))
                                                     ),                                          
                                                 array(array('PRA S',array()),array('KS I',array()))
                                                );

                                break;
                       case 3 : $html_txt = "<center><bold>KB DAN NON KB BERDASARKAN STATUS PRA S DAN KS I </bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                                      array($nmklm,array('rowspan'=>'2')),
                                                      array('JUMLAH KK',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PUS',array('rowspan'=>'2')),
                                                      array('KB (PUS)',array('colspan'=>'3')),
                                                      array('NON KB (PUS)',array('colspan'=>'3'))
                                                     ),                                          
                                                 array(array('PRA S',array()),array('KS I',array()),array('JUMLAH',array()),array('PRA S',array()),array('KS I',array()),array('JUMLAH',array()))
                                                );

                                break;
                     }
                     break;
          }

       }else{
           switch($ks)
          {
            case 1 : switch($kb)
                     {
                       case 1 :   $html_txt = "<center><bold>DAFTAR KELUARGA STATUS PUS DAN KB</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KKI',array('rowspan'=>'2')),
                                                      array('KEPALA KELUARGA',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PESERTA KB',array('colspan'=>$numrows))
                                                     ),                                          
                                                 $nmcontyp
                                                );

                                break;
                       case 2 : $html_txt = "<center><bold>DAFTAR KELUARGA NON KB</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KKI',array()),
                                                      array('KEPALA KELUARGA',array()),
                                                      array('JUMLAH JIWA',array()),
                                                      array('PUS',array())
                                                     )
                                                );

                                break;
                       case 3 : $html_txt = "<center><bold>DAFTAR KELUARGA STATUS KB & NON KB</bold><br>$subjudul</center>";
                                  $jdl_tb = array(array(array('NO. KKI',array()),
                                                      array('KEPALA KELUARGA',array()),
                                                      array('JUMLAH JIWA',array()),
                                                      array('PUS',array()),
                                                      array('KB',array()),
                                                      array('NON KB',array())
                                                     )
                                                );

                                break;
                     }
                     break;
            case 2 : switch($kb)
                     {
                       case 1 : $html_txt = "<center><bold>DAFTAR KELUARGA PUS STATUS KB, PRA S & KS I</bold><br>$subjudul</center>";
                                $jdl_tb = array(array(array('NO. KKI',array('rowspan'=>'2')),
                                                      array('KEPALA KELUARGA',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PRA S',array('colspan'=>$numrows)),
                                                      array('KS I',array('colspan'=>$numrows))
                                                     ),                                          
                                                 $nmcontyp
                                                );

                                break;
                       case 2 : $html_txt = "<center><bold>DAFTAR KELUARGA PUS STATUS NON KB, PRA S DAN KS I</bold><br>$subjudul</center>";
                                $jdl_tb = array(array(array('NO. KKI',array('rowspan'=>'2')),
                                                      array('KEPALA KELUARGA',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('TAHAPAN KS',array('colspan'=>'2'))
                                                     ),                                          
                                                 array(array('PRA S',array()),array('KS I',array()))
                                                );

                                break;
                       case 3 : $html_txt = "<center><bold>DAFTAR KELUARGA KB DAN NON KB BERDASARKAN STATUS PRA S DAN KS I</bold><br>$subjudul</center>";
                                $jdl_tb = array(array(array('NO. KKI',array('rowspan'=>'2')),
                                                      array('KEPALA KELUARGA',array('rowspan'=>'2')),
                                                      array('JUMLAH JIWA',array('rowspan'=>'2')),
                                                      array('PUS',array('rowspan'=>'2')),
                                                      array('KB',array('colspan'=>'2')),
                                                      array('NON KB',array('colspan'=>'2'))
                                                     ),                                          
                                                 array(array('PRA S',array()),array('KS I',array()),array('PRA S',array()),array('KS I',array()))
                                                );

                                break;
                     }
                     break;
          }
       }        
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   } 

   function menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'JUMLAH':'DAFTAR')." KK DAN PUS, PESERTA KB PER METODE KONTRASEPSI</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

          $dt_contr = new dt_contr_typ;
          $nmcontyp = $dt_contr->getnm('',empty($idrt) ? 1:0,0,0);
          $numrows=$dt_contr->getnumrows();    

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu02($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('PUS',array('rowspan'=>'2')),
                                               array('PESERTA KB PER METODE KONTRASEPSI',array('colspan'=>$numrows+1)),
                                               array('TINGKAT PREVALENSI KB ',array('rowspan'=>'2'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA',array('rowspan'=>'2')),
                        array('PUS',array('rowspan'=>'2')),
                        array('PESERTA KB',array('colspan'=>$numrows))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       $nmcontyp
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

   function menu421_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'JUMLAH':'DAFTAR')." KK DAN JIWA</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);
       
       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu421($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3'))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       array(array('LAKI-LAKI',array()),
                        array('PEREMPUAN',array()),
                        array('JUMLAH',array()))
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

   function menu422_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur){
                  
        switch($cmbumur)
        {
          case 1 : $umur = 'SAMA DENGAN '.$dtumur[0].' TAHUN' ;break;
          case 2 : $umur = 'KECIL DARI '.$dtumur[0].' TAHUN' ;break;
          case 3 : $umur = 'BESAR DARI '.$dtumur[0].' TAHUN' ;break;
          case 4 : $umur = $dtumur[0].' - '.$dtumur[1].' TAHUN' ;break; 
        }

         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'JUMLAH JIWA':'DAFTAR INDIVIDU')." UMUR $umur</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);
       
       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu422($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = empty($idrt) ? $tmp['footer_tb'] : ''; 

       

       $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3'))
                                               ),                                          
                       array(array('LAKI-LAKI',array()),
                        array('PEREMPUAN',array()),
                        array('JUMLAH',array()))
                      );

       if(!empty($idrt)){
          
          $jdl_tb = array(array(array('Kode Anggota Keluarga',array()),
                        array('Nama',array()),
                        array('Jenis Kelamin',array()),
                        array('Status Keluarga',array()),
                        array('Tgl Lahir',array())
                        ));

       }

       
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

   function menu423_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur,$cmbkerja){
                  
        switch($cmbumur)
        {
          case 1 : $umur = 'SAMA DENGAN '.$dtumur[0].' TAHUN' ;break;
          case 2 : $umur = 'KECIL DARI '.$dtumur[0].' TAHUN' ;break;
          case 3 : $umur = 'BESAR DARI '.$dtumur[0].' TAHUN' ;break;
          case 4 : $umur = $dtumur[0].' - '.$dtumur[1].' TAHUN' ;break; 
        }

        $kerja = array(1=>'BEKERJA',2=>'TIDAK BEKERJA');

         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'JUMLAH JIWA':'DAFTAR INDIVIDU')." UMUR $umur $kerja[$cmbkerja]</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);
       
       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu423($idkec,$iddesa,$iddusun,$idrt,$cmbumur,$dtumur,$cmbkerja);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = empty($idrt) ? $tmp['footer_tb'] : ''; 

       

       $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3'))
                                               ),                                          
                       array(array('LAKI-LAKI',array()),
                        array('PEREMPUAN',array()),
                        array('JUMLAH',array()))
                      );

       if(!empty($idrt)){
          
          $jdl_tb = array(array(array('Kode Anggota Keluarga',array()),
                        array('Nama',array()),
                        array('Jenis Kelamin',array()),
                        array('Status Keluarga',array()),
                        array('Tgl Lahir',array())
                        ));

       }

       
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

   function menu424_hslfilter($idkec,$iddesa,$iddusun,$idrt,$cmbsekolah){
                  
        $sekolah = array(1=>'SEKOLAH',2=>'TIDAK SEKOLAH');

         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? '':'DAFTAR INDIVIDU')." USIA SEKOLAH 5-12, 13-15, 16-18 TAHUN $sekolah[$cmbsekolah]</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);
       
       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu424($idkec,$iddesa,$iddusun,$idrt,$cmbsekolah);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = empty($idrt) ? $tmp['footer_tb'] : ''; 

       

       $jdl_tb = array(array(array('NO. KODE',array('rowspan'=>'3')),
                             array($nmklm,array('rowspan'=>'3')),
                             array('USIA SEKOLAH',array('colspan'=>'9')),
                             array('TOTAL',array('rowspan'=>'3'))
                                  ),                                          
                       array(array('7-12 TAHUN',array('colspan'=>'3')),
                             array('13-15 TAHUN',array('colspan'=>'3')),
                             array('16-18 TAHUN',array('colspan'=>'3'))
                             ),
                       array(array('LAKI-LAKI',array()),
                             array('PEREMPUAN',array()),
                             array('JUMLAH',array()),
                             array('LAKI-LAKI',array()),
                             array('PEREMPUAN',array()),
                             array('JUMLAH',array()),
                             array('LAKI-LAKI',array()),
                             array('PEREMPUAN',array()),
                             array('JUMLAH',array())
                        )
                      );

       if(!empty($idrt)){
          
          $jdl_tb = array(array(array('KODE ANGGOTA KELUARGA',array('rowspan'=>'2')),
                                array('NAMA',array('rowspan'=>'2')),
                                array('JENIS KELAMIN',array('rowspan'=>'2')),
                                array('TGL LAHIR',array('rowspan'=>'2')),
                                array('USIA SEKOLAH',array('colspan'=>'3'))
                               ),
                             array(array('7-12 TAHUN',array()),
                             array('13-15 TAHUN',array()),
                             array('16-18 TAHUN',array())
                             ) 
                         );

       }

       
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

   function menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>".(empty($idrt) ? 'JUMLAH':'DAFTAR')." PUS NON KB PER ALASAN</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

       $tb_contr = new tb_gen('dbo_non_acptr_reas');
       $data = $tb_contr->getData('');  

       $numrows=$tb_contr->numrows;    

       $nmcontyp=array();
       if(!empty($data)){
           foreach($data as $row)
           {
             $nmcontyp[]=array(strtoupper($row['Nm_nonacptr_ind']),array()); 
           }
          
        }

       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu03($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('JUMLAH JIWA',array('rowspan'=>'2')),
                                               array('ALASAN NON KB',array('colspan'=>$numrows))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA',array('rowspan'=>'2')),
                        array('ALASAN NON KB',array('colspan'=>$numrows))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       $nmcontyp
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

      function menu04_hslfilter($idkec,$iddesa,$iddusun,$idrt){
                  
         $subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
         $html_txt = "<center><bold>TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
       
       $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);
       
       $dt_rekap = new dt_rekapitulasi;   
       $tmp_dt_tb = $dt_rekap->getdtmenu04($idkec,$iddesa,$iddusun,$idrt);
       
       $tmp = $this->build_dt_tb($tmp_dt_tb);
       $dt_tb = $tmp['dt_tb'];
       $txt = $tmp['footer_tb']; 

       $row_1 = array(array('NO. KODE',array('rowspan'=>'2')),
                                               array($nmklm,array('rowspan'=>'2')),
                                               array('JUMLAH KK',array('rowspan'=>'2')),
                                               array('JUMLAH JIWA',array('rowspan'=>'2')),
                                               array('TAHAPAN KS',array('colspan'=>'5'))
                                               );

       if(!empty($idrt)){
          $row_1 = array(array('NO. KKI',array('rowspan'=>'2')),
                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
                        array('JUMLAH JIWA',array('rowspan'=>'2')),
                        array('TAHAPAN KS',array('colspan'=>'5'))
                        );
       }

       $jdl_tb = array($row_1,                                          
                       array(array('PRA S',array()),
                             array('KS I',array()),
                             array('KS II',array()),
                             array('KS III',array()),
                             array('KS III+',array())
                             )
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   $jdl_tb,
                                   $dt_tb,$txt);

       $html_txt .= $tb_hslfilter->display();   

       return $html_txt; 
   }

}

?>   