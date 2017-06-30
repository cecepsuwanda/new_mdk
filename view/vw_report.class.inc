<?php require_once('shared.php');
     
class vw_report
{
   function __construct() {
		$this->tb_header = array('id'=>'tbhslfilter','width'=>'100%');
   }

   function menu_filter($hide=array(),$show=array(),$okshow=array()){
   	 $frmfilter = new frm_filter;
   	 $html_txt = $frmfilter->cmb_filter($hide,$show,$okshow)."<br><br>";
   	 $html_txt .= "<div id='data'>";
   	 $html_txt .= "</div>";
   	 return $html_txt; 
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

   private function getnmklm($idkec,$iddesa,$iddusun,$idrt)
  {
    $nmklm='KECAMATAN';
    $nmklm= $idkec ? 'DESA/KELURAHAN' : $nmklm;
    $nmklm= $iddesa ? 'DUSUN/RW' : $nmklm;
    $nmklm= $iddusun ? 'RT' : $nmklm;   
    return $nmklm;    
  }

  private function getjudul($idkec,$iddesa,$iddusun,$idrt)
  {
             
    $subjudul='KABUPATEN/KOTA';         
    $subjudul= ($idkec>0) ? 'KECAMATAN' : $subjudul;        
    $subjudul= ($iddesa>0) ?'DESA/KELURAHAN' : $subjudul;
    $subjudul= ($iddusun>0) ? 'DUSUN/RW' : $subjudul;   
    $subjudul= ($idrt>0) ? 'RT' : $subjudul;         

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

   private function build_nocol($jml,$start=1)
  {
    $nocol=array();
    for($i=$start;$i<=$jml;$i++)
    {
      $nocol[]=array($i,array('bgcolor'=>'#99CCFF'));
    } 
    return $nocol;
  }

  

   function menu01_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>DAFTAR KEPALA KELUARGA</bold><br>$subjudul</center>";
		
		//$dt_report = new dt_report;   
		//$tmp_dt_tb = $dt_report->getdtmenu01($idkec,$iddesa,$iddusun,$idrt);
		
		
		//$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = null;//$tmp['dt_tb'];
		$txt = '';//$tmp['footer_tb']; 
		
		
		$tb_hslfilter = new mytable(array('id'=>'tbserverside','width'=>'100%'),
		                            array(
									                      array(array('NO. KKI',array()),
		                                          array("KEPALA KELUARGA",array()),
		                                          array('JUMLAH JIWA',array())
												                    )
		                                  ),
		                           $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

  function menu01_ss_viewdata($param){
    $dt_report = new dt_report;   
    
    
    $data = $dt_report->getdtmenu01($param['idkec'],$param['iddesa'],$param['iddusun'],$param['idrt'],(intval($param['iDisplayStart'])/intval($param['iDisplayLength']))+1,intval($param['iDisplayLength']),$param['sSearch'],array($param['iSortCol_0'],$param['sSortDir_0']));
    
       $totalrecords=$data['totaldata'];
       $totaldisplayrecords=$data['displaydata'];

    $output = array('sEcho' => intval($param['sEcho']),
                    'iTotalRecords' => $totalrecords,
                    'iTotalDisplayRecords' => $totaldisplayrecords,
                    'aaData'=>array()   
      );

    if(!empty($data['data']))
    {
      foreach ($data['data'] as $row) {        
        $output['aaData'][]=$row;
      }
    }

    return $output;
  }

  function menu02_tab1_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    ini_set('memory_limit','-1');

    $dt_unit = new dt_unit_detail;
    $nm_kecamatan = $dt_unit->getnm("id_unit_detail='$idkec'");
    $nm_kelurahan = $dt_unit->getnm("id_unit_detail='$iddesa'");

    
              $sub = array(
                           array('MENGIKUTI POSYANDU',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK MENGIKUTI POSYANDU',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('MENGIKUTI POSYANDU',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK MENGIKUTI POSYANDU',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('NAMA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELOMPOK UMUR',array('colspan'=>'3','bgcolor'=>'#99CCFF'))                           
                           );
                          
    $tb_contr_src = new tb_gen('dbo_contr_src');
    $dt_contr_src = $tb_contr_src->getData('');

    if(!empty($dt_contr_src))
    {
      foreach ($dt_contr_src as $row) {
        $sub[]=array(strtoupper($row['Nm_consrc_ind']),array('rowspan'=>'2','bgcolor'=>'#99CCFF'));
      }
    }

    $sub[]=array('PESERTA KB YANG IMPLANNYA AKAN DICABUT TAHUN DEPAN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'));

    $dt_non = new dt_non_acptr_reas;
    $sub = $dt_non->getnm('',0,$sub,array('rowspan'=>'2','bgcolor'=>'#99CCFF')); 


    $nocol = $this->build_nocol(48);

    $jdltbl =  array(
                      array(
                           array('NO URUT RUMAH TANGGA',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),
                           array('NO URUT KEPALA KELUARGA',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),
                           array('KELUARGA',array('colspan'=>'46','bgcolor'=>'#99CCFF'))
                           ),
                      array(
                           array('NAMA KEPALA KELUARGA',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT JENIS KELAMIN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PEKERJAAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PERKAWINAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT TINGKAT PENDIDIKAN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA MENDAPATKAN KREDIT MIKRO/BANTUAN MODAL',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH WANITA USIA SUBUR (15-49) TAHUN',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('JUMLAH KEMATIAN 1 TAHUN TERAKHIR',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH ANGGOTA KELUARGA MENURUT KELOMPOK UMUR',array('colspan'=>'16','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'12','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('LAKI-LAKI',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BEKERJA',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TIDAK BEKERJA',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('KAWIN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('DUDA/JANDA/BELUM KAWIN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TIDAK TAMAT SD',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TAMAT SD - SLTP',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TAMAT SLTA',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TAMAT AK/PT',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('YA',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('TIDAK',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('IBU HAMIL/MELAHIRKAN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('UMUR < 1',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BAYI < 1 TAHUN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('BALITA 1 - < 5 TAHUN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('5 - 6 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('7 - 12 TAHUN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('13 - 15 TAHUN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('16 - 21 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('22 - 59 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('60 TAHUN KEATAS',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('NO URUT PUS',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('ISTERI',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('PESERTA KB',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BUKAN PESERTA KB',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           ),
                     $sub,
                     array(
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('< 20 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('20 - 29 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('30 - 49 TAHUN',array('bgcolor'=>'#99CCFF'))
                           ),
                     $nocol
                     );
    
    $html_tab1 = "<center><bold>REGISTER PENDATAAN KELUARGA</bold><br><br></center>";
    
    if(empty($iddusun)){
     $data_dusun = $dt_unit->getdusun($iddesa);    
    }else{      
      $data_dusun = $dt_unit->getdata("id_unit=13 AND id_unit_detail_idk='$iddesa' AND id_unit_detail='$iddusun'");
    }
    
    $i=1;
    if(!empty($data_dusun))
    {
      $dt_report = new dt_report;
      foreach($data_dusun as $row)
       {  
          if(empty($idrt))
          {   
             $data_rt = $dt_unit->getrt($row['id_unit_detail']);
          }else{
             $data_rt = $dt_unit->getdata("id_unit=14 AND id_unit_detail_idk='$row[id_unit_detail]' and id_unit_detail='$idrt'"); 
          } 

           if(!empty($data_rt))
           {
             foreach ($data_rt as $row1) {
              
             
              $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'300px'),
                                array(),
                                array(array(array('JUMLAH KELUARGA YANG ADA',array()),array(' : ',array()),array('',array())),
                                      array(array('RT',array()),array(' : ',array()),array($row1['no_unit_detail'],array())),
                                      array(array('DUSUN/RW',array()),array(' : ',array()),array($row['no_unit_detail'],array())),
                                      array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($nm_kelurahan,array())),
                                      array(array('KECAMATAN',array()),array(' : ',array()),array($nm_kecamatan,array())),
                                      array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array())),
                                      array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array())) 
                                     ),'');    
    
              $html_tab1 .='<center>'.$tb_judul->display('').'</center><br><br>';
              $html_tab1 .='A. DATA DEMOGRAFI DAN KB<br>';

               $tmp_dt_tb = $dt_report->getdtmenu02_tab1($idkec,$iddesa,$row['id_unit_detail'],$row1['id_unit_detail']); 
               
               $txt = '<tr>';
               $txt .= "<th colspan='2' bgcolor='#000000'></th><th>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row1'])){ 
               $j=1;               
               foreach ($tmp_dt_tb['footer_tb']['row1'] as $key => $value) {
                  if($j==35){
                    $txt .= "<th align='center' bgcolor='#000000' ></th>";
                  }else{ 
                    $txt .= "<th align='center'>$value</th>";
                  }
                  $j++;
                }
               }

               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='48'><B>KELUARGA PRA SEJAHTERA DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2' bgcolor='#000000'></th><th>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row2'])){                
               $j=1;
               foreach ($tmp_dt_tb['footer_tb']['row2'] as $key => $value) {
                  if($j==35){
                    $txt .= "<th align='center' bgcolor='#000000' ></th>";
                  }else{ 
                    $txt .= "<th align='center'>$value</th>";
                  }
                  $j++;
                }
               }                            
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='48'><B>KELUARGA SEJAHTERA I DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2'bgcolor='#000000'></th><th>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row3'])){                
               $j=1;
               foreach ($tmp_dt_tb['footer_tb']['row3'] as $key => $value) {
                  if($j==35){
                    $txt .= "<th align='center' bgcolor='#000000' ></th>";
                  }else{ 
                    $txt .= "<th align='center'>$value</th>";
                  }
                  $j++;
                }
               }
               $txt .= '</tr>';
    
               $tmp_dt_tb['footer_tb']=array();

               $tmp = $this->build_dt_tb($tmp_dt_tb);
               $dt_tb = $tmp['dt_tb'];
               

               $tb_tab1 = new mytable(array('id'=>'tbtab1'.$i++,'width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab1 .= $tb_tab1->display().'<br><br>';

             }
           }
       }
    }

    return $html_tab1;

  }  

  function menu02_tab2_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    ini_set('memory_limit','-1');

    $dt_unit = new dt_unit_detail;
    $nm_kecamatan = $dt_unit->getnm("id_unit_detail='$idkec'");
    $nm_kelurahan = $dt_unit->getnm("id_unit_detail='$iddesa'"); 

    $dt_indk_ks = new dt_indikator_ks;
    $nm = $dt_indk_ks->getnm('id_ind_ks>=6 and id_ind_ks<=36',0,0,0,array('bgcolor'=>'#99CCFF'));
    $jml = $dt_indk_ks->getnumrows();

    $nm[]=array('KELUARGA PRA SEJAHTERA',array('bgcolor'=>'#99CCFF'));
    $nm[]=array('KELUARGA SEJAHTERA I',array('bgcolor'=>'#99CCFF'));
    $nm[]=array('KELUARGA SEJAHTERA II',array('bgcolor'=>'#99CCFF'));
    $nm[]=array('KELUARGA SEJAHTERA III',array('bgcolor'=>'#99CCFF'));
    $nm[]=array('KELUARGA SEJAHTERA III PLUS',array('bgcolor'=>'#99CCFF'));

    
    $jdltbl =  array(array(
                        array('NO URUT RUMAH TANGGA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                        array('NO URUT KEPALA KELUARGA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                        array('INDIKATOR KELUARGA SEJAHTERA',array('colspan'=>$jml,'bgcolor'=>'#99CCFF')),
                        array('TAHAPAN KELUARGA SEJAHTEA',array('colspan'=>'5','bgcolor'=>'#99CCFF'))
                      ),
                      $nm                 
                     );
    
    $html_tab2 = "";
    
    if(empty($iddusun)){
     $data_dusun = $dt_unit->getdusun($iddesa);    
    }else{      
      $data_dusun = $dt_unit->getdata("id_unit=13 AND id_unit_detail_idk='$iddesa' AND id_unit_detail='$iddusun'");
    }    
    
    $i=1;
    if(!empty($data_dusun))
    {
      $dt_report = new dt_report;
      foreach($data_dusun as $row)
       {  
          if(empty($idrt))
          {   
             $data_rt = $dt_unit->getrt($row['id_unit_detail']);
          }else{
             $data_rt = $dt_unit->getdata("id_unit=14 AND id_unit_detail_idk='$row[id_unit_detail]' and id_unit_detail='$idrt'"); 
          }
           if(!empty($data_rt))
           {
             foreach ($data_rt as $row1) {
              
             
              $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'300px'),
                                array(),
                                array(array(array('JUMLAH KELUARGA YANG ADA',array()),array(' : ',array()),array('',array())),
                                      array(array('RT',array()),array(' : ',array()),array($row1['no_unit_detail'],array())),
                                      array(array('DUSUN/RW',array()),array(' : ',array()),array($row['no_unit_detail'],array())),
                                      array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($nm_kelurahan,array())),
                                      array(array('KECAMATAN',array()),array(' : ',array()),array($nm_kecamatan,array())),
                                      array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array())),
                                      array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array())) 
                                     ),'');    
    
              $html_tab2 .='<center>'.$tb_judul->display('').'</center><br><br>';
              $html_tab2 .='B. TAHAPAN KELUARGA SEJAHTERA<br>';

               $tmp_dt_tb = $dt_report->getdtmenu02_tab2($idkec,$iddesa,$row['id_unit_detail'],$row1['id_unit_detail']);
               
               $txt = "<tr><th align='center' bgcolor='#000000' colspan='27' >";
               
               if(isset($tmp_dt_tb['footer_tb']['row1'])){
                  foreach ($tmp_dt_tb['footer_tb']['row1'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }     
               
               $txt .="</tr>";
               $txt .= "<tr>
                           <th align='center' bgcolor='#000000'></th>
                           <th align='center' >V</th>";
               
               if(isset($tmp_dt_tb['footer_tb']['row2'])){
                  foreach ($tmp_dt_tb['footer_tb']['row2'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";
               $txt .= "<tr>
                           <th align='center' bgcolor='#000000'></th>
                           <th align='center' >X</th>";               
               if(isset($tmp_dt_tb['footer_tb']['row3'])){
                  foreach ($tmp_dt_tb['footer_tb']['row3'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";
               $txt .= "<tr>
                           <th align='center' bgcolor='#000000'></th>
                           <th align='center' >-</th>";               
               if(isset($tmp_dt_tb['footer_tb']['row4'])){
                  foreach ($tmp_dt_tb['footer_tb']['row4'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";
               $txt .= "<tr>
                           <th align='center' bgcolor='#000000'></th>
                           <th align='center' >X*</th>";               
               if(isset($tmp_dt_tb['footer_tb']['row5'])){
                  foreach ($tmp_dt_tb['footer_tb']['row5'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";
               $txt .= "<tr><th align='center' colspan='32'>KELUARGA MENURUT INDIKATOR PRA SEJAHTERA</th></tr>";
               $txt .= "<tr>
                            <th align='center' bgcolor='#000000'></th>
                            <th align='center' >X & X*</th>";               
               if(isset($tmp_dt_tb['footer_tb']['row6'])){
                  foreach ($tmp_dt_tb['footer_tb']['row6'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";
               $txt .= "<tr><th align='center' colspan='32'>KELUARGA MENURUT INDIKATOR SEJAHTERA I</th></tr>";
               $txt .= "<tr>
                            <th align='center' bgcolor='#000000'></th>
                            <th align='center' >X & X*</th>";               
               if(isset($tmp_dt_tb['footer_tb']['row7'])){
                  foreach ($tmp_dt_tb['footer_tb']['row7'] as $key => $value) {
                    $txt .= "<th align='center'>$value</th>";
                  }
               }
               $txt .= "<th align='center' bgcolor='#000000' colspan='5'></th>"; 
               $txt .= "</tr>";

    
               $tmp_dt_tb['footer_tb']=array();

               $tmp = $this->build_dt_tb($tmp_dt_tb);
               $dt_tb = $tmp['dt_tb'];
                 
    
               $tb_tab2 = new mytable(array('id'=>'tbtab2'.$i++,'width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab2 .= $tb_tab2->display().'<br><br>';

             }
           }
       }
    }

    return $html_tab2;

  }

  function menu02_tab3_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    ini_set('memory_limit','-1');
    $dt_unit = new dt_unit_detail;
    $nm_kecamatan = $dt_unit->getnm("id_unit_detail='$idkec'");
    $nm_kelurahan = $dt_unit->getnm("id_unit_detail='$iddesa'"); 

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('INDIVIDU ANGGOTA KELUARGA',array('colspan'=>'10','bgcolor'=>'#99CCFF'))
                           ),
                      array(
                           array('NOMOR KODE KELUARGA INDONESIA',array('bgcolor'=>'#99CCFF')),
                           array('NOMOR KODE ANGGOTA KELUARGA',array('bgcolor'=>'#99CCFF')),
                           array('NAMA',array('bgcolor'=>'#99CCFF')),
                           array('HUBUNGAN DENGAN KK',array('bgcolor'=>'#99CCFF')),
                           array('JENIS KELAMIN',array('bgcolor'=>'#99CCFF')),
                           array('TANGGAL BULAN DAN TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('PEKERJAAN',array('bgcolor'=>'#99CCFF')),
                           array('PENDIDIKAN TERAKHIR',array('bgcolor'=>'#99CCFF')),
                           array('STATUS PERKAWINAN',array('bgcolor'=>'#99CCFF')),
                           array('PERUBAHAN MUTASI',array('bgcolor'=>'#99CCFF'))
                           )
                     );
    
    $html_tab3 = "";
    
    if(empty($iddusun)){
     $data_dusun = $dt_unit->getdusun($iddesa);    
    }else{      
      $data_dusun = $dt_unit->getdata("id_unit=13 AND id_unit_detail_idk='$iddesa' AND id_unit_detail='$iddusun'");
    }    
    
    $i=1;
    if(!empty($data_dusun))
    {
      $dt_report = new dt_report;

      foreach($data_dusun as $row)
       {  
          $nmdusun = $row['no_unit_detail'];
           if(empty($idrt))
          {   
             $data_rt = $dt_unit->getrt($row['id_unit_detail']);
          }else{
             $data_rt = $dt_unit->getdata("id_unit=14 AND id_unit_detail_idk='$row[id_unit_detail]' and id_unit_detail='$idrt'"); 
          }
           if(!empty($data_rt))
           {
             foreach ($data_rt as $row1) {
              
             
              $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'300px'),
                                array(),
                                array(array(array('JUMLAH KELUARGA YANG ADA',array()),array(' : ',array()),array('',array())),
                                      array(array('RT',array()),array(' : ',array()),array($row1['no_unit_detail'],array())),
                                      array(array('DUSUN/RW',array()),array(' : ',array()),array($nmdusun,array())),
                                      array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($nm_kelurahan,array())),
                                      array(array('KECAMATAN',array()),array(' : ',array()),array($nm_kecamatan,array())),
                                      array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array())),
                                      array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array())) 
                                     ),'');    
    
              $html_tab3 .='<center>'.$tb_judul->display('').'</center><br><br>';
              $html_tab3 .='C. DATA ANGGOTA KELUARGA<br>';

               $tmp_dt_tb = $dt_report->getdtmenu02_tab3($idkec,$iddesa,$row['id_unit_detail'],$row1['id_unit_detail']); 
               //$tmp = $this->build_dt_tb($tmp_dt_tb);
               $dt_tb = array();//$tmp['dt_tb'];

               if(!empty($tmp_dt_tb))
               {
                 $tmp = array();
                 $i=1;
                 foreach($tmp_dt_tb as $kdfam=>$row2)
                 {
                    
                    $tmp[]=array($i++,array('rowspan'=>$row2['jml'],'align'=>'center'));                 
                    
                    foreach($row2['data'] as $data_row)
                    {                                            
                      foreach ($data_row as $row3) {
                        $tmp[]=array($row3,array('align'=>'center'));
                      }                    
                      $dt_tb[]=$tmp;
                      $tmp = array();                  
                    }
                     unset($tmp_dt_tb[$kdfam]['jml']);
                     unset($tmp_dt_tb[$kdfam]['data']);
                     unset($tmp_dt_tb[$kdfam]);
                      
                 }
                  unset($tmp_dt_tb);
               }               

               $txt = '';//$tmp['footer_tb']; 
    
    
               $tb_tab3 = new mytable(array('id'=>'tbtab3'.$i++,'width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab3 .= $tb_tab3->display().'<br><br>';

             }
           }
       }
    }

    return $html_tab3;

  }

  function menu02_tab4_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    $dt_unit = new dt_unit_detail;
    $nm_kecamatan = $dt_unit->getnm("id_unit_detail='$idkec'");
    $nm_kelurahan = $dt_unit->getnm("id_unit_detail='$iddesa'"); 

    $nocol = $this->build_nocol(19);

    $jdltbl =  array(
                      array(
                           array('NO',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'6','bgcolor'=>'#99CCFF')),
                           array('HASIL PEMBINAAN KESERTAAN BER KB',array('colspan'=>'12','bgcolor'=>'#99CCFF'))
                           ),
                      array(
                           array('NAMA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('UMUR ISTRI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH ANAK',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('UMUR ANAK TERKECIL',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TAHAPAN KS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JANUARI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('FEBRUARI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('MARET',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('APRIL',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('MEI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUNI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JULI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('AGUSTUS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEPTEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('OKTOBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('NOVEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('DESEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('ISTRI',array('bgcolor'=>'#99CCFF')),
                           array('SUAMI',array('bgcolor'=>'#99CCFF')),
                           ),
                     $nocol
                     );
    
    
    
    if(empty($iddusun)){
     $data_dusun = $dt_unit->getdusun($iddesa);    
    }else{      
      $data_dusun = $dt_unit->getdata("id_unit=13 AND id_unit_detail_idk='$iddesa' AND id_unit_detail='$iddusun'");
    }    
    
    $html_tab4='';
    $i=1;
    if(!empty($data_dusun))
    {
      $dt_report = new dt_report;
      foreach($data_dusun as $row)
       {  
          $nmdusun = $row['no_unit_detail'];
          
           if(empty($idrt))
          {   
             $data_rt = $dt_unit->getrt($row['id_unit_detail']);
          }else{
             $data_rt = $dt_unit->getdata("id_unit=14 AND id_unit_detail_idk='$row[id_unit_detail]' and id_unit_detail='$idrt'"); 
          }

          if(!empty($data_rt))
           {
             foreach ($data_rt as $row1) {
              
             
              $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'300px'),
                                array(),
                                array(array(array('JUMLAH KELUARGA YANG ADA',array()),array(' : ',array()),array('',array())),
                                      array(array('RT',array()),array(' : ',array()),array($row1['no_unit_detail'],array())),
                                      array(array('DUSUN/RW',array()),array(' : ',array()),array($nmdusun,array())),
                                      array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($nm_kelurahan,array())),
                                      array(array('KECAMATAN',array()),array(' : ',array()),array($nm_kecamatan,array())),
                                      array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array())),
                                      array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array())) 
                                     ),'');    
    
               $html_tab4 .= "<center><bold>REGISTER KELOMPOK KB BAGI SELURUH KELUARGA</bold><br><br></center>";
               $html_tab4 .='<center>'.$tb_judul->display('').'</center><br><br>';
              
               
               $tmp_dt_tb = $dt_report->getdtmenu02_tab4($idkec,$iddesa,isset($row['id_unit_detail']) ? $row['id_unit_detail'] :'',isset($row1['id_unit_detail']) ? $row1['id_unit_detail'] : ''); 
               //$tmp = $this->build_dt_tb($tmp_dt_tb);
               $dt_tb = null;//$tmp['dt_tb'];
               
               if(!empty($tmp_dt_tb['data']))
               {
                 
                 $j=1;
                 foreach ($tmp_dt_tb['data'] as $row2) {
                   $tmp = array();
                   $tmp[]=array($j++,array());  
                   
                   foreach ($row2 as $row3) {
                    $tmp[]=array($row3,array('align'=>'center'));
                   }

                   for($k=1;$k<=12;$k++) {
                        $tmp[]=array('',array('align'=>'center'));
                      }


                   $dt_tb[]=$tmp;
                      
                 }
               }
    
               unset($tmp_dt_tb);
               $klmjdl=array();
               $klmjdl[1]=array(array('1. Jumlah Pasangan Usia Subur (PUS)',array('align'=>'left','colspan'=>'2')));
               $klmjdl[2]=array(array('2. Jumlah Peserta KB Aktif',array('align'=>'left','colspan'=>'2')));
               $klmjdl[3]=array(array('ALKON',array('align'=>'center')),array('KODE',array('align'=>'center')));
               
               $i=4;
               $dt = new dt_contr_typ;
               $data = $dt->getdata('');

               foreach ($data as $row) {
                 $klmjdl[$i][]=array(chr(ord('a')+($i-4)).'. '.$row['Nm_contyp_ind'],array('align'=>'left','style'=>'border-right-style: none;'));
                 $klmjdl[$i][]=array('('.$row['singkatan'].')',array('align'=>'center','style'=>'border-left-style: none;'));

                 $i++;
               }

               $klmjdl[$i++]=array(array('3. Jumlah Peserta KB Aktif Menurut Tempat Pelayanan',array('align'=>'left','colspan'=>'2')));
               
               $tb = new tb_gen('dbo_contr_src');
               $data = $tb->getData('');
               
               foreach ($data as $row) {
                 $klmjdl[$i][]=array($row['Nm_consrc_ind'],array('align'=>'left','colspan'=>'2'));
                 $i++;
               }

               $klmjdl[$i++]=array(array('4. Jumlah Pasangan Usia Subur Bukan Peserta KB',array('align'=>'left','colspan'=>'2')));
               
               $klmjdl[$i][]=array('a. Hamil',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(H)',array('align'=>'center','style'=>'border-left-style: none;'));

               $klmjdl[$i][]=array('b. Ingin Anak Segera',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(IAS)',array('align'=>'center','style'=>'border-left-style: none;'));
 
               $klmjdl[$i][]=array('c. Ingin Anak Ditunda',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(IAT)',array('align'=>'center','style'=>'border-left-style: none;'));
               
               $klmjdl[$i][]=array('d. Tidak Ingin Anak Lagi',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(TIAL)',array('align'=>'center','style'=>'border-left-style: none;'));

               $klmjdl[$i++]=array(array('<I>PARAF KETUA KELOMPOK KB</I>',array('align'=>'center','colspan'=>'3')));
               $klmjdl[$i++]=array(array('<I>PARAF Sub PPKBD</I>',array('align'=>'center','colspan'=>'3')));

               $txt='';
               for($i=1;$i<=21;$i++){  
                 $txt .='<tr>';
                   if($i==1){
                    $txt .='<th rowspan="19" bgcolor="#333333" ></th>';
                   }
                 
                   foreach($klmjdl[$i] as $row){                      
                        $txt .='<th';
                        foreach ($row[1] as $key => $value) {
                          $txt .=" $key='$value'";
                        }
                        $txt .='>'.$row[0].'</th>';
                   }
                 

                 $txt .='<th colspan="4" bgcolor="#333333" ></th>';
                      for($k=1;$k<=12;$k++) {
                        $txt .='<th></th>';
                      }                     

                 $txt .='</tr>';
                }


               $tb_tab4 = new mytable(array('id'=>'tbtab4'.$i++,'width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab4 .= $tb_tab4->display().'<br><br>';

             }
           }
       }
    }

    return $html_tab4;

  }

  function menu02_tab5_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    $dt_unit = new dt_unit_detail;
    $nm_kecamatan = $dt_unit->getnm("id_unit_detail='$idkec'");
    $nm_kelurahan = $dt_unit->getnm("id_unit_detail='$iddesa'"); 

    $nocol = $this->build_nocol(19);

        $jdltbl =  array(
                      array(
                           array('NO',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'6','bgcolor'=>'#99CCFF')),
                           array('HASIL PEMBINAAN KESERTAAN BER KB',array('colspan'=>'12','bgcolor'=>'#99CCFF'))
                           ),
                      array(
                           array('NAMA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('UMUR ISTRI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH ANAK',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('UMUR ANAK TERKECIL',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TAHAPAN KS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JANUARI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('FEBRUARI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('MARET',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('APRIL',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('MEI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUNI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JULI',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('AGUSTUS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEPTEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('OKTOBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('NOVEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('DESEMBER',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('ISTRI',array('bgcolor'=>'#99CCFF')),
                           array('SUAMI',array('bgcolor'=>'#99CCFF')),
                           ),
                     $nocol
                     );
    
    
    
    if(empty($iddusun)){
     $data_dusun = $dt_unit->getdusun($iddesa);    
    }else{      
      $data_dusun = $dt_unit->getdata("id_unit=13 AND id_unit_detail_idk='$iddesa' AND id_unit_detail='$iddusun'");
    }    
    
    $html_tab5='';
    $i=1;
    if(!empty($data_dusun))
    {
      $dt_report = new dt_report;
      foreach($data_dusun as $row)
       {  
          $nmdusun = $row['no_unit_detail'];
          if(empty($idrt))
          {   
             $data_rt = $dt_unit->getrt($row['id_unit_detail']);
          }else{
             $data_rt = $dt_unit->getdata("id_unit=14 AND id_unit_detail_idk='$row[id_unit_detail]' and id_unit_detail='$idrt'"); 
          }

           if(!empty($data_rt))
           {
             foreach ($data_rt as $row1) {
                         
              $html_tab5 .= "<center><bold>REGISTER KELOMPOK KB BAGI KELUARGA PRA SEJAHTERA DAN KELUARGA SEJAHTERA I </bold><br><br></center>";
              $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'300px'),
                                array(),
                                array(array(array('JUMLAH KELUARGA YANG ADA',array()),array(' : ',array()),array('',array())),
                                      array(array('RT',array()),array(' : ',array()),array($row1['no_unit_detail'],array())),
                                      array(array('DUSUN/RW',array()),array(' : ',array()),array($nmdusun,array())),
                                      array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($nm_kelurahan,array())),
                                      array(array('KECAMATAN',array()),array(' : ',array()),array($nm_kecamatan,array())),
                                      array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array())),
                                      array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array())) 
                                     ),'');    
    
              $html_tab5 .='<center>'.$tb_judul->display('').'</center><br><br>';
              

               $tmp_dt_tb = $dt_report->getdtmenu02_tab5($idkec,$iddesa,isset($row['id_unit_detail']) ? $row['id_unit_detail'] :'',isset($row1['id_unit_detail']) ? $row1['id_unit_detail'] : ''); 
               //$tmp = $this->build_dt_tb($tmp_dt_tb);
               $dt_tb = null;//$tmp['dt_tb'];
               $txt = '';//$tmp['footer_tb']; 

               if(!empty($tmp_dt_tb['data']))
               {
                 
                 $j=1;
                 foreach ($tmp_dt_tb['data'] as $row2) {
                   $tmp = array();
                   $tmp[]=array($j++,array());  
                   
                   foreach ($row2 as $row3) {
                    $tmp[]=array($row3,array('align'=>'center'));
                   }

                   for($k=1;$k<=12;$k++) {
                        $tmp[]=array('',array('align'=>'center'));
                      }


                   $dt_tb[]=$tmp;
                      
                 }
               }

               unset($tmp_dt_tb);

               $klmjdl=array();
               $klmjdl[1]=array(array('1. Jumlah Pasangan Usia Subur (PUS)',array('align'=>'left','colspan'=>'2')));
               $klmjdl[2]=array(array('2. Jumlah Peserta KB Aktif',array('align'=>'left','colspan'=>'2')));
               $klmjdl[3]=array(array('ALKON',array('align'=>'center')),array('KODE',array('align'=>'center')));
               
               $i=4;
               $dt = new dt_contr_typ;
               $data = $dt->getdata('');

               foreach ($data as $row) {
                 $klmjdl[$i][]=array(chr(ord('a')+($i-4)).'. '.$row['Nm_contyp_ind'],array('align'=>'left','style'=>'border-right-style: none;'));
                 $klmjdl[$i][]=array('('.$row['singkatan'].')',array('align'=>'center','style'=>'border-left-style: none;'));

                 $i++;
               }

               $klmjdl[$i++]=array(array('3. Jumlah Peserta KB Aktif Menurut Tempat Pelayanan',array('align'=>'left','colspan'=>'2')));
               
               $tb = new tb_gen('dbo_contr_src');
               $data = $tb->getData('');
               
               foreach ($data as $row) {
                 $klmjdl[$i][]=array($row['Nm_consrc_ind'],array('align'=>'left','colspan'=>'2'));
                 $i++;
               }

               $klmjdl[$i++]=array(array('4. Jumlah Pasangan Usia Subur Bukan Peserta KB',array('align'=>'left','colspan'=>'2')));
               
               $klmjdl[$i][]=array('a. Hamil',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(H)',array('align'=>'center','style'=>'border-left-style: none;'));

               $klmjdl[$i][]=array('b. Ingin Anak Segera',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(IAS)',array('align'=>'center','style'=>'border-left-style: none;'));
 
               $klmjdl[$i][]=array('c. Ingin Anak Ditunda',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(IAT)',array('align'=>'center','style'=>'border-left-style: none;'));
               
               $klmjdl[$i][]=array('d. Tidak Ingin Anak Lagi',array('align'=>'left','style'=>'border-right-style: none;'));
               $klmjdl[$i++][]=array('(TIAL)',array('align'=>'center','style'=>'border-left-style: none;'));

               $klmjdl[$i++]=array(array('<I>PARAF KETUA KELOMPOK KB</I>',array('align'=>'center','colspan'=>'3')));
               $klmjdl[$i++]=array(array('<I>PARAF Sub PPKBD</I>',array('align'=>'center','colspan'=>'3')));

               $txt='';
               for($i=1;$i<=21;$i++){  
                 $txt .='<tr>';
                   if($i==1){
                    $txt .='<th rowspan="19" bgcolor="#333333" ></th>';
                   }
                 
                   foreach($klmjdl[$i] as $row){                      
                        $txt .='<th';
                        foreach ($row[1] as $key => $value) {
                          $txt .=" $key='$value'";
                        }
                        $txt .='>'.$row[0].'</th>';
                   }
                 

                 $txt .='<th colspan="4" bgcolor="#333333" ></th>';
                      for($k=1;$k<=12;$k++) {
                        $txt .='<th></th>';
                      }                     

                 $txt .='</tr>';
                }
    
               $tb_tab5 = new mytable(array('id'=>'tbtab5'.$i++,'width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab5 .= $tb_tab5->display().'<br><br>';

             }
           }
       }
    }

    return $html_tab5;

  }

  function menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    
    //$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);

    $html_tab1 = '';//$this->menu02_tab1_hslfilter($idkec,$iddesa,$iddusun,$idrt);
    $html_tab2 = '';//$this->menu02_tab2_hslfilter($idkec,$iddesa,$iddusun,$idrt);
    $html_tab3 = '';//$this->menu02_tab3_hslfilter($idkec,$iddesa,$iddusun,$idrt);
    $html_tab4 = '';//$this->menu02_tab4_hslfilter($idkec,$iddesa,$iddusun,$idrt);
    $html_tab5 = '';//$this->menu02_tab5_hslfilter($idkec,$iddesa,$iddusun,$idrt);       
    
    $tab = new mytabs('tabhslfilter',array('A. Data Demografi dan KB',
                                          'B. Tahapan Keluarga Sejahtera',
                                          'C. Data Anggota Keluarga',
                                          'Register Kelompok KB Bagi Seluruh Keluarga',
                                          'Register Kelompok KB Bagi Keluarga PRA S & KS I'),array($html_tab1,$html_tab2,$html_tab3,$html_tab4,$html_tab5));
    $html_txt = $tab->display("onClick='tab_click(this,$idkec,$iddesa,$iddusun,$idrt);'");
    return $html_txt; 
  }
  
  private function getjdltab($idkec,$iddesa,$iddusun,$idrt,$jml=0)
  {
    $jdl=array();

    $dtunit = new dt_unit_detail;
    $jdl[] = array(array('JUMLAH '.$this->getnmklm($idkec,$iddesa,$iddusun,$idrt).' YANG ADA',array()),array(' : ',array()),array($jml,array()));
                
   if($iddusun>0){
      $jdl[] = array(array('DUSUN/RW',array()),array(' : ',array()),array($dtunit->getnm("id_unit_detail='$iddusun'"),array()),
                     array('NO. KODE DUSUN/RW',array('align'=>'right')),array(' : ',array()),array(' '.$iddusun,array()));
   }
   if($iddesa>0){
      $jdl[] =array(array('DESA/KELURAHAN',array()),array(' : ',array()),array($dtunit->getnm("id_unit_detail='$iddesa'"),array()),
                    array('NO. KODE DESA/KELURAHAN',array('align'=>'right')),array(' : ',array()),array(' '.$iddesa,array()));
   }
   
   if($idkec>0){
      $jdl[] = array(array('KECAMATAN',array()),array(' : ',array()),array($dtunit->getnm("id_unit_detail='$idkec'"),array()),
                     array('NO. KODE KECAMATAN',array('align'=>'right')),array(' : ',array()),array(' '.$idkec,array()));
   }
   $jdl[] = array(array('KABUPATEN/KOTA',array()),array(' : ',array()),array(' KABUPATEN BANDUNG BARAT',array()),
                  array('NO. KODE KABUPATEN/KOTA',array('align'=>'right')),array(' : ',array()),array(' 1017',array()));
   $jdl[] = array(array('PROVINSI',array()),array(' : ',array()),array(' JAWA BARAT',array()),
                  array('NO. KODE PROVINSI',array('align'=>'right')),array(' : ',array()),array(' 10',array())); 
    

    return $jdl;
  }


  function menu03_tab1_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   ini_set('memory_limit','-1');   
   $html_tab1 = "<center><bold>REKAPITULASI HASIL PENDATAAN KELUARGA TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab1($idkec,$iddesa,$iddusun,$idrt);    
   
   $footerspan = 9;
   $footerspan -= $idkec>0 ? 2 : 0;
   $footerspan -= $iddesa>0 ? 2 : 0;
   $footerspan -= $iddusun>0 ? 2 : 0;

    $jcolspan = 28;
    $jcolspan -= $idkec>0 ? 2 : 0;
    $jcolspan -= $iddesa>0 ? 2 : 0;
    $jcolspan -= $iddusun>0 ? 2 : 0; 

               $txt = '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row1'])){ 
                              
               foreach ($tmp_dt_tb['footer_tb']['row1'] as $key => $value) {                   
                    $txt .= "<th align='center'>$value</th>";                  
                }
               }

               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='$jcolspan'><B>KELUARGA PRA SEJAHTERA DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th><th colspan='$footerspan' bgcolor='#000000'></th>";
               if(isset($tmp_dt_tb['footer_tb']['row2'])){                
              
               foreach ($tmp_dt_tb['footer_tb']['row2'] as $key => $value) {
                     $txt .= "<th align='center'>$value</th>"; 
                }
               }                            
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='$jcolspan'><B>KELUARGA SEJAHTERA I DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th><th colspan='$footerspan' bgcolor='#000000'></th>";
               if(isset($tmp_dt_tb['footer_tb']['row3'])){                
               
               foreach ($tmp_dt_tb['footer_tb']['row3'] as $key => $value) {
                   
                    $txt .= "<th align='center'>$value</th>";
                  
                }
               }
               $txt .= '</tr>';

   $tmp_dt_tb['footer_tb']=array();
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   //$txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt);               
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                                array(),$jdl,'');    
    
    $html_tab1 .='<center>'.$tb_judul->display('').'</center><br><br>';

    $jnocol = 28;
    $jnocol -= $idkec>0 ? 2 : 0;
    $jnocol -= $iddesa>0 ? 2 : 0;
    $jnocol -= $iddusun>0 ? 2 : 0;

    $jcolspan = 6;
    $jcolspan -= $idkec>0 ? 2 : 0;
    $jcolspan -= $iddesa>0 ? 2 : 0;
    $jcolspan -= $iddusun>0 ? 2 : 0;


    $nocol = $this->build_nocol($jnocol);

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array($this->getnmklm($idkec,$iddesa,$iddusun,$idrt),array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('CAKUPAN WILAYAH',array('colspan'=>$jcolspan,'bgcolor'=>'#99CCFF')),
                           array('CAKUPAN RUMAH TANGGA DAN KELUARGA',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA',array('colspan'=>'16','bgcolor'=>'#99CCFF'))
                           ),
                      array(
                           array('JUMLAH DESA/KELURAHAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH DUSUN/RW',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH RUKUN TETANGGA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH RUMAH TANGGA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH KEPALA KELUARGA',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT JENIS KELAMIN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PEKERJAAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PERKAWINAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT TINGKAT PENDIDIKAN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA MENDAPATKAN KREDIT MIKRO/BANTUAN MODAL',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('JUMLAH WANITA USIA SUBUR (15-49) TAHUN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('YANG ADA',array('bgcolor'=>'#99CCFF')),
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('YANG ADA',array('bgcolor'=>'#99CCFF')),
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('YANG ADA',array('bgcolor'=>'#99CCFF')),
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('YANG ADA',array('bgcolor'=>'#99CCFF')),
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('YANG ADA',array('bgcolor'=>'#99CCFF')),
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('DUDA/JANDA/BELUM KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK TAMAT SD',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SD - SLTP',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SLTA',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT AK/PT',array('bgcolor'=>'#99CCFF')),
                           array('YA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('JUMLAH',array('bgcolor'=>'#99CCFF'))                           
                           ),                     
                     $nocol
                     );
                
                if($idkec>0)
                {
                 unset($jdltbl[1][0]);
                 unset($jdltbl[2][0]);
                 unset($jdltbl[2][1]);
                }

                if($iddesa>0)
                {
                 unset($jdltbl[1][1]);
                 unset($jdltbl[2][2]);
                 unset($jdltbl[2][3]);
                }

                if($iddusun>0)
                {
                 unset($jdltbl[0][2]); 
                 unset($jdltbl[1][2]);
                 unset($jdltbl[2][4]);
                 unset($jdltbl[2][5]);
                }

                

                $tb_tab1 = new mytable(array('id'=>'tbtab1','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab1 .= $tb_tab1->display().'<br><br>';
   
   return $html_tab1;     
  } 

  function menu03_tab2_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab2($idkec,$iddesa,$iddusun,$idrt);    
   
               $txt = '<tr>';
               if(isset($tmp_dt_tb['footer_tb']['row1'])){ 
                 foreach ($tmp_dt_tb['footer_tb']['row1'] as $key => $value) {                   
                    $txt .= "<th align='center'>$value</th>";                  
                }
               }

               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='30'><B>KELUARGA PRA SEJAHTERA DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               if(isset($tmp_dt_tb['footer_tb']['row2'])){             
               foreach ($tmp_dt_tb['footer_tb']['row2'] as $key => $value) {
                     $txt .= "<th align='center'>$value</th>"; 
                }
               }
               $txt .="<th colspan='6' bgcolor='#000000'></th>";                           
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='30'><B>KELUARGA SEJAHTERA I DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               if(isset($tmp_dt_tb['footer_tb']['row3'])){                
               
               foreach ($tmp_dt_tb['footer_tb']['row3'] as $key => $value) {
                   
                    $txt .= "<th align='center'>$value</th>";
                  
                }
               }
               $txt.="<th colspan='6' bgcolor='#000000'></th>";
               $txt.='</tr>';

   $tmp_dt_tb['footer_tb']=array();
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   //$txt = $tmp['footer_tb'];

   $html_tab2='';

          $sub = array(
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELOMPOK UMUR',array('colspan'=>'3','bgcolor'=>'#99CCFF'))                           
                           );
                          
    $tb_contr_src = new tb_gen('dbo_contr_src');
    $dt_contr_src = $tb_contr_src->getData('');

    if(!empty($dt_contr_src))
    {
      foreach ($dt_contr_src as $row) {
        $sub[]=array(strtoupper($row['Nm_consrc_ind']),array('rowspan'=>'2','bgcolor'=>'#99CCFF'));
      }
    }

    $sub[]=array('PESERTA KB YANG IMPLANNYA AKAN DICABUT TAHUN DEPAN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'));

    $dt_non = new dt_non_acptr_reas;
    $sub = $dt_non->getnm('',0,$sub,array('rowspan'=>'2','bgcolor'=>'#99CCFF')); 


    $nocol = $this->build_nocol(51,23);

    $jdltbl =  array(
                      array(                           
                           array('KELUARGA',array('colspan'=>'23','bgcolor'=>'#99CCFF')),
                           array('HASIL PENTAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'6','bgcolor'=>'#99CCFF'))
                           ),
                      array(                           
                           array('JUMLAH JIWA KELOMPOK UMUR',array('colspan'=>'16','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'7','bgcolor'=>'#99CCFF')),
                           array('KELUARGA PRA SEJAHTERA',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA SEJAHTERA I',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA SEJAHTERA II',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA SEJAHTERA III',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA SEJAHTERA III PLUS',array('rowspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('JUMLAH',array('rowspan'=>'4','bgcolor'=>'#99CCFF'))

                           ),
                     array(                           
                           array('BAYI 0 < 1 TAHUN MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('BALITA 1 - < 5 TAHUN  MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('5 - 6 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('7 - 15 TAHUN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                           
                           array('16 - 21 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('22 - 59 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('60 TAHUN KEATAS',array('rowspan'=>'3','bgcolor'=>'#99CCFF')), 
                           array('JUMLAH',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                          
                           array('PESERTA KB',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BUKAN PESERTA KB',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           ),
                     $sub,
                     array(
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('< 20 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('20 - 29 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('30 - 49 TAHUN',array('bgcolor'=>'#99CCFF'))
                           ),
                     $nocol
                     );
               

               $tb_tab2 = new mytable(array('id'=>'tbtab2','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab2 .= $tb_tab2->display().'<br><br>';
 
   return $html_tab2;     
  }

  function menu03_tab3_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab3="<center><bold>REKAPITULASI PESERTA KB PER MIX KONTRASEPSI HASIL PENDATAAN KELUARGA TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab3($idkec,$iddesa,$iddusun,$idrt);    
  
               $txt = '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row1'])){ 
                              
               foreach ($tmp_dt_tb['footer_tb']['row1'] as $key => $value) {                   
                    $txt .= "<th align='center'>$value</th>";                  
                }
               }

               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='13'><B>KELUARGA PRA SEJAHTERA DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row2'])){                
              
               foreach ($tmp_dt_tb['footer_tb']['row2'] as $key => $value) {
                     $txt .= "<th align='center'>$value</th>"; 
                }
               }                            
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='13'><B>KELUARGA SEJAHTERA I DAN ANGGOTA KELUARGA</B></th>";
               $txt .= '</tr>';
               $txt .= '<tr>';
               $txt .= "<th colspan='2'>JUMLAH</th>";
               if(isset($tmp_dt_tb['footer_tb']['row3'])){                
               
               foreach ($tmp_dt_tb['footer_tb']['row3'] as $key => $value) {
                   
                    $txt .= "<th align='center'>$value</th>";
                  
                }
               }
               $txt .= '</tr>';

   $tmp_dt_tb['footer_tb']=array();

   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   //$txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt);               
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                                array(),$jdl,'');    
    
   $html_tab3 .='<center>'.$tb_judul->display('').'</center><br><br>';
   
   $nocol = $this->build_nocol(13);

          $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

          $dt_contr = new dt_contr_typ;
          $nmcontyp = array();
          $nmcontyp = $dt_contr->getnm('',0,1,0,$nmcontyp,array('bgcolor'=>'#99CCFF'));
          $numrows=$dt_contr->getnumrows();    
       
       $row_1 = array(array('NO. URUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array($nmklm,array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('JUMLAH PUS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('PESERTA KB PER METODE KONTRASEPSI',array('colspan'=>$numrows+1,'bgcolor'=>'#99CCFF')),
                      array('TINGKAT PREVALENSI KB ',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                    );       

       $jdl_tb = array($row_1,                                          
                       $nmcontyp,
                       $nocol
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbtab3','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                   $jdl_tb,
                                   $dt_tb,$txt);
       
       $html_tab3 .= $tb_hslfilter->display();

   return $html_tab3;     
  }

  function menu03_tab4_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab4="<center><bold>REKAPITULASI PESERTA KB PER MIX KONTRASEPSI HASIL PENDATAAN KELUARGA TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab4($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt); 
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                               array(),$jdl,'');    
    
   $html_tab4 .='<center>'.$tb_judul->display('').'</center><br><br>';


   $nocol = $this->build_nocol(14);

          $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

          $dt_contr = new dt_contr_typ;
          $nmcontyp = array();
          $nmcontyp = $dt_contr->getnm('',0,1,0,$nmcontyp,array('bgcolor'=>'#99CCFF'));
          $numrows=$dt_contr->getnumrows();    
       
       $row_1 = array(array('NO. URUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array($nmklm,array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('STATUS KELUARGA PRA SEJAHTERA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('JUMLAH PUS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('PESERTA KB PER METODE KONTRASEPSI',array('colspan'=>$numrows+1,'bgcolor'=>'#99CCFF')),
                      array('TINGKAT PREVALENSI KB ',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                    );       

       $jdl_tb = array($row_1,                                          
                       $nmcontyp,
                       $nocol
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbtab4','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                   $jdl_tb,
                                   $dt_tb,$txt);
       
       $html_tab4 .= $tb_hslfilter->display();

   return $html_tab4;     
  }

  function menu03_tab5_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab5="<center><bold>REKAPITULASI PESERTA KB PER MIX KONTRASEPSI HASIL PENDATAAN KELUARGA TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab5($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt);               
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                                array(),$jdl,'');    
    
   $html_tab5 .='<center>'.$tb_judul->display('').'</center><br><br>';
   
   $nocol = $this->build_nocol(14);

          $nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

          $dt_contr = new dt_contr_typ;
          $nmcontyp = array();
          $nmcontyp = $dt_contr->getnm('',0,1,0,$nmcontyp,array('bgcolor'=>'#99CCFF'));
          $numrows=$dt_contr->getnumrows();    
       
       $row_1 = array(array('NO. URUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array($nmklm,array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('STATUS KELUARGA KS I',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('JUMLAH PUS',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                      array('PESERTA KB PER METODE KONTRASEPSI',array('colspan'=>$numrows+1,'bgcolor'=>'#99CCFF')),
                      array('TINGKAT PREVALENSI KB ',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                    );       

       $jdl_tb = array($row_1,                                          
                       $nmcontyp,
                       $nocol
                      );
       
       $tb_hslfilter = new mytable(array('id'=>'tbtab5','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                   $jdl_tb,
                                   $dt_tb,$txt);
       
       $html_tab5 .= $tb_hslfilter->display();

    

   return $html_tab5;     
  }

  function menu03_tab6_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab6="<center><bold>REKAPITULASI HASIL PEMUTAKHIRAN DATA KELUARGA PRA SEJAHTERA TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab6($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt);               
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                                array(),$jdl,'');    
    
   $html_tab6 .='<center>'.$tb_judul->display('').'</center><br><br>';

    $jnocol = 20;

    $nocol = $this->build_nocol($jnocol);

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array($this->getnmklm($idkec,$iddesa,$iddusun,$idrt),array('rowspan'=>'3','bgcolor'=>'#99CCFF')),                           
                           array('STATUS KELUARGA PRA SEJAHTERA',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('JUMLAH KEPALA KELUARGA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELUARGA',array('colspan'=>'16','bgcolor'=>'#99CCFF'))
                           ),
                      array(                          
                           array('KEPALA KELUARGA MENURUT JENIS KELAMIN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PEKERJAAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PERKAWINAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT TINGKAT PENDIDIKAN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA MENDAPATKAN KREDIT MIKRO/BANTUAN MODAL',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('JUMLAH WANITA USIA SUBUR (15-49) TAHUN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('DUDA/JANDA/BELUM KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK TAMAT SD',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SD - SLTP',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SLTA',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT AK/PT',array('bgcolor'=>'#99CCFF')),
                           array('YA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('JUMLAH',array('bgcolor'=>'#99CCFF'))                           
                           ),                     
                     $nocol
                     );
                
                


                $tb_tab6 = new mytable(array('id'=>'tbtab6','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab6 .= $tb_tab6->display().'<br><br>';

   return $html_tab6;     
  }

  function menu03_tab7_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab7($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $html_tab7=''; 
   
          $sub = array(
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELOMPOK UMUR',array('colspan'=>'3','bgcolor'=>'#99CCFF'))                           
                           );
                          
    $tb_contr_src = new tb_gen('dbo_contr_src');
    $dt_contr_src = $tb_contr_src->getData('');

    if(!empty($dt_contr_src))
    {
      foreach ($dt_contr_src as $row) {
        $sub[]=array(strtoupper($row['Nm_consrc_ind']),array('rowspan'=>'2','bgcolor'=>'#99CCFF'));
      }
    }

    $sub[]=array('PESERTA KB YANG IMPLANNYA AKAN DICABUT TAHUN DEPAN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'));

    $dt_non = new dt_non_acptr_reas;
    $sub = $dt_non->getnm('',0,$sub,array('rowspan'=>'2','bgcolor'=>'#99CCFF')); 


    $nocol = $this->build_nocol(46,21);

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),
                           array($this->getnmklm($idkec,$iddesa,$iddusun,$idrt),array('rowspan'=>'5','bgcolor'=>'#99CCFF')),                           
                           array('STATUS KELUARGA PRA SEJAHTERA',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),                           
                           array('KELUARGA',array('colspan'=>'23','bgcolor'=>'#99CCFF'))
                           ),
                      array(                           
                           array('JUMLAH JIWA KELOMPOK UMUR',array('colspan'=>'16','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'7','bgcolor'=>'#99CCFF'))
                           ),
                     array(                           
                           array('BAYI 0 < 1 TAHUN MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('BALITA 1 - < 5 TAHUN  MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('5 - 6 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('7 - 15 TAHUN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                           
                           array('16 - 21 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('22 - 59 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('60 TAHUN KEATAS',array('rowspan'=>'3','bgcolor'=>'#99CCFF')), 
                           array('JUMLAH',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                          
                           array('PESERTA KB',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BUKAN PESERTA KB',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           ),
                     $sub,
                     array(
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('< 20 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('20 - 29 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('30 - 49 TAHUN',array('bgcolor'=>'#99CCFF'))
                           ),
                     $nocol
                     );
               

               $tb_tab7 = new mytable(array('id'=>'tbtab7','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab7 .= $tb_tab7->display().'<br><br>';

   return $html_tab7;     
  }

  function menu03_tab8_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab8=''; 
   
   return $html_tab8;     
  }

  function menu03_tab9_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab9="<center><bold>REKAPITULASI HASIL PEMUTAKHIRAN DATA KELUARGA SEJAHTERA I TINGKAT ".$this->getjudul($idkec,$iddesa,$iddusun,$idrt)."</bold><br><br></center>"; 
   

   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab9($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $jdl=$this->getjdltab($idkec,$iddesa,$iddusun,$idrt);               
   $tb_judul = new mytable(array('id'=>'tbjudul','width'=>'600px'),
                                array(),$jdl,'');    
    
   $html_tab9 .='<center>'.$tb_judul->display('').'</center><br><br>';

   $jnocol = 20;

    $nocol = $this->build_nocol($jnocol);

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array($this->getnmklm($idkec,$iddesa,$iddusun,$idrt),array('rowspan'=>'3','bgcolor'=>'#99CCFF')),                           
                           array('STATUS KELUARGA KS I',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('JUMLAH KEPALA KELUARGA',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELUARGA',array('colspan'=>'16','bgcolor'=>'#99CCFF'))
                           ),
                      array(                          
                           array('KEPALA KELUARGA MENURUT JENIS KELAMIN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PEKERJAAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT STATUS PERKAWINAN',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KEPALA KELUARGA MENURUT TINGKAT PENDIDIKAN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           array('KELUARGA MENDAPATKAN KREDIT MIKRO/BANTUAN MODAL',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('JUMLAH JIWA DALAM KELUARGA',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('JUMLAH WANITA USIA SUBUR (15-49) TAHUN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'))
                           ),
                     array(
                           array('YANG DI DATA',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK BEKERJA',array('bgcolor'=>'#99CCFF')),
                           array('KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('DUDA/JANDA/BELUM KAWIN',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK TAMAT SD',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SD - SLTP',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT SLTA',array('bgcolor'=>'#99CCFF')),
                           array('TAMAT AK/PT',array('bgcolor'=>'#99CCFF')),
                           array('YA',array('bgcolor'=>'#99CCFF')),
                           array('TIDAK',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('JUMLAH',array('bgcolor'=>'#99CCFF'))                           
                           ),                     
                     $nocol
                     );
                
                


                $tb_tab9 = new mytable(array('id'=>'tbtab9','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab9 .= $tb_tab9->display().'<br><br>';


   return $html_tab9;     
  }

  function menu03_tab10_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   
   $dt_report = new dt_report;
   $tmp_dt_tb = $dt_report->getdtmenu03_tab10($idkec,$iddesa,$iddusun,$idrt);    
   $tmp = $this->build_dt_tb($tmp_dt_tb);
   $dt_tb = $tmp['dt_tb'];
   $txt = $tmp['footer_tb'];


   $html_tab10=''; 
    
   
          $sub = array(
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK IKUT',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('TIDAK SEKOLAH',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('rowspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('KELOMPOK UMUR',array('colspan'=>'3','bgcolor'=>'#99CCFF'))                           
                           );
                          
    $tb_contr_src = new tb_gen('dbo_contr_src');
    $dt_contr_src = $tb_contr_src->getData('');

    if(!empty($dt_contr_src))
    {
      foreach ($dt_contr_src as $row) {
        $sub[]=array(strtoupper($row['Nm_consrc_ind']),array('rowspan'=>'2','bgcolor'=>'#99CCFF'));
      }
    }

    $sub[]=array('PESERTA KB YANG IMPLANNYA AKAN DICABUT TAHUN DEPAN',array('rowspan'=>'2','bgcolor'=>'#99CCFF'));

    $dt_non = new dt_non_acptr_reas;
    $sub = $dt_non->getnm('',0,$sub,array('rowspan'=>'2','bgcolor'=>'#99CCFF')); 


    $nocol = $this->build_nocol(46,21);

    $jdltbl =  array(
                      array(
                           array('NO URUT',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),
                           array($this->getnmklm($idkec,$iddesa,$iddusun,$idrt),array('rowspan'=>'5','bgcolor'=>'#99CCFF')),                           
                           array('STATUS KELUARGA KS I',array('rowspan'=>'5','bgcolor'=>'#99CCFF')),                           
                           array('KELUARGA',array('colspan'=>'23','bgcolor'=>'#99CCFF'))
                           ),
                      array(                           
                           array('JUMLAH JIWA KELOMPOK UMUR',array('colspan'=>'16','bgcolor'=>'#99CCFF')),
                           array('PASANGAN USIA SUBUR',array('colspan'=>'7','bgcolor'=>'#99CCFF'))
                           ),
                     array(                           
                           array('BAYI 0 < 1 TAHUN MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('BALITA 1 - < 5 TAHUN  MENGIKUTI KEGIATAN POSYANDU',array('colspan'=>'2','bgcolor'=>'#99CCFF')),
                           array('5 - 6 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('7 - 15 TAHUN',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                           
                           array('16 - 21 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('22 - 59 TAHUN',array('rowspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('60 TAHUN KEATAS',array('rowspan'=>'3','bgcolor'=>'#99CCFF')), 
                           array('JUMLAH',array('colspan'=>'4','bgcolor'=>'#99CCFF')),                          
                           array('PESERTA KB',array('colspan'=>'3','bgcolor'=>'#99CCFF')),
                           array('BUKAN PESERTA KB',array('colspan'=>'4','bgcolor'=>'#99CCFF')),
                           ),
                     $sub,
                     array(
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('LAKI-LAKI',array('bgcolor'=>'#99CCFF')),
                           array('PEREMPUAN',array('bgcolor'=>'#99CCFF')),
                           array('< 20 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('20 - 29 TAHUN',array('bgcolor'=>'#99CCFF')),
                           array('30 - 49 TAHUN',array('bgcolor'=>'#99CCFF'))
                           ),
                     $nocol
                     );
               

               $tb_tab10 = new mytable(array('id'=>'tbtab10','width'=>'100%','border'=>'2','cellpadding'=>'8','cellspacing'=>'0','style'=>'border-collapse: collapse'),
                                          $jdltbl,
                                          $dt_tb,$txt);

               $html_tab10 .= $tb_tab10->display().'<br><br>';

   return $html_tab10;     
  }

  function menu03_tab11_hslfilter($idkec,$iddesa,$iddusun,$idrt){
   $html_tab11=''; 
   
   return $html_tab11;     
  }

  function menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt){
    
    //$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);

    $html_tab1 = '';
    $html_tab2 = '';
    $html_tab3 = '';
    $html_tab4 = '';
    $html_tab5 = '';
    $html_tab6 = '';
    $html_tab7 = '';
    $html_tab8 = '';
    $html_tab9 = '';
    $html_tab10 = '';
    $html_tab11 = '';
    
    $tab = new mytabs('tabhslfilter',array('R/I/K S/07 Hal 1',
                                           'R/I/K S/07 Hal 2',
                                           'R/I/K S/Peserta KB/09',
                                           'R/I/Pra S/Peserta KB/09',
                                           'R/I/K S I/Peserta KB/09',
                                           'R/I/Kel. Pra S/07 Hal 1',
                                           'R/I/Kel. Pra S/07 Hal 2',
                                           'Indikator Tahapan Keluarga PRA S',
                                           'R/I/Kel. K S I/07 Hal 1',
                                           'R/I/Kel. K S I/07 Hal 2',
                                           'Indikator Tahapan Keluarga K S I'
                                          ),
                                           array($html_tab1,
                                                 $html_tab2,
                                                 $html_tab3,
                                                 $html_tab4,
                                                 $html_tab5,
                                                 $html_tab6,
                                                 $html_tab7,
                                                 $html_tab8,
                                                 $html_tab9,
                                                 $html_tab10,
                                                 $html_tab11
                                                 )
                                           );
    $html_txt .= $tab->display("onClick='tab_click(this,$idkec,$iddesa,$iddusun,$idrt);'");
    return $html_txt; 
  }
}   