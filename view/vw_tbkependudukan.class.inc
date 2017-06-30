<?php require_once('shared.php');

class vw_tbkependudukan
{
    private $tb_header; 

	function __construct() {
	   $this->tb_header = array('id'=>'tbhslfilter','width'=>'100%');	
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

	private function getfooternmklm($idkec,$iddesa,$iddusun,$idrt)
	{
		$dt = new dt_unit_detail;
		$nm = 'KABUPATEN BANDUNG BARAT';
		$nm = ($idkec!=0) ?  'KECAMATAN '.$dt->getnm("id_unit_detail='$idkec'") : $nm;
		$nm = ($iddesa!=0) ? 'DESA/KELURAHAN '.$dt->getnm("id_unit_detail='$iddesa'") : $nm;
		$nm = ($iddusun!=0) ? 'DUSUN/RW '.$dt->getnm("id_unit_detail='$iddusun'") : $nm;      
		
		return $nm;
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

	private function build_nocol($jml)
	{
		$nocol=array();
		for($i=1;$i<=$jml;$i++)
		{
			$nocol[]=array($i,array());
		} 
		return $nocol;
	}

	private function dt_berulang($ulang,$data)
	{
		$tmp=array();
		for($i=1;$i<=$ulang;$i++){
           foreach($data as $row)
           {
           	 $tmp[]=array($row,array());
           } 
		}
		return $tmp;
	}

	function menu01_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA KERJA MENURUT KELOMPOK UMUR DAN JENIS PEKERJAAN</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu01($idkec,$iddesa,$iddusun,$idrt);
		
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_empmnt = new dt_empmnt_stat;		
		$empmnt=$dt_empmnt->getnm('Kd_emp!=6');
		$numrows=$dt_empmnt->getnumrows();
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
									      array(
										        array('NO. KODE',array('rowspan'=>'3')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'3')),
		                                        array('JENIS PEKERJAAN',array('colspan'=>($numrows+2))),
		                                        array('JUMLAH',array('rowspan'=>'3'))
												),
		                                   array(
										         array('BEKERJA',array('colspan'=>($numrows+1))),
		                                         array('TIDAK BEKERJA',array('rowspan'=>'2'))
											    ),
		                                  $empmnt),
		                           $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();   

		return $html_txt; 
	}

	function menu02_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA KERJA MENURUT KELOMPOK UMUR JENIS KELAMIN DAN BERSTATUS BEKERJA</bold><br>$subjudul</center>";
		
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu02($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','PEREMPUAN','JUMLAH'));

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
									        array(
											    array('NO. KODE',array('rowspan'=>'2')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                        array('JUMLAH JIWA USIA KERJA',array('colspan'=>'3')),
		                                        array('JUMLAH JIWA YANG BERSTATUS KERJA',array('colspan'=>'3'))
											),
		                                  $dt_ulang
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu03_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA PEMILIH MENURUT KELOMPOK UMUR JENIS KELAMIN DAN STATUS DALAM KELUARGA</bold><br>$subjudul</center>";  
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu03($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','PEREMPUAN')); 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
									        array(
									            array('NO. KODE',array('rowspan'=>'2')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                        array('KEPALA KELUARGA',array('rowspan'=>'2')),
		                                        array('ISTRI',array('rowspan'=>'2')),
		                                        array('ANAK',array('colspan'=>'2')),
		                                        array('LAINNYA',array('colspan'=>'2')),
		                                        array('JUMLAH',array('rowspan'=>'2'))
		                                    ),
		                                    $dt_ulang
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu04_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA PEMILIH MENURUT KELOMPOK UMUR JENIS KELAMIN DAN STATUS DALAM KELUARGA</bold><br>$subjudul</center>";  
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu04($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','PEREMPUAN'));		

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
									      array(
										         array('NO. KODE',array('rowspan'=>'2')),
		                                         array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                         array('KEPALA KELUARGA',array('rowspan'=>'2')),
		                                         array('ISTRI',array('rowspan'=>'2')),
		                                         array('ANAK',array('colspan'=>'2')),
		                                         array('LAINNYA',array('colspan'=>'2')),
		                                         array('JUMLAH',array('rowspan'=>'2'))
		                                       ),
		                                  $dt_ulang
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();   

		return $html_txt; 
	}

	function menu05_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PESERTA KB MENURUT KELOMPOK UMUR METODE KONTRASEPSI DAN JUMLAH ANAK</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu05($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_contr = new dt_contr_typ;
		$nmcontyp=$dt_contr->getnm('');  
        $nmcontyp[]=array('1',array());
		$nmcontyp[]=array('2',array());
		$nmcontyp[]=array('3',array());
		$nmcontyp[]=array('>3',array());
		$numrows=$dt_contr->getnumrows();

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											     array('NO. KODE',array('rowspan'=>'2')),
		                                         array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                         array('METODE KONTASEPSI',array('colspan'=>($numrows+1))),
		                                         array('JUMLAH ANAK',array('colspan'=>'4'))
		                                        ),
		                                   $nmcontyp
		                             ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu06_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS DAN PUS PESERTA KB, PUS BUKAN PESERTA KB MENURUT KELOMPOK UMUR DAN ALASAN TIDAK BER-KB</bold><br>$subjudul</center>";

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu06($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];	

		$dt_contr = new dt_non_acptr_reas;
		$nmnonacptr=$dt_contr->getnm('');  
		$numrows=$dt_contr->getnumrows();
		
		$tb_hslfilter = new mytable($this->tb_header,
		                             array(
										    array(
												   array('NO. KODE',array('rowspan'=>'2')),
		                                           array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                           array('JUMLAH PUS',array('rowspan'=>'2')),
		                                           array('PUS PESERTA KB',array('rowspan'=>'2')),
		                                           array('PUS BUKAN PESERTA KB',array('colspan'=>($numrows+1)))
		                                    ),
		                                    $nmnonacptr
		                                  ),
		                             $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu07_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA MENURUT KELOMPOK UMUR DAN JENIS KELAMIN</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu07($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											     array('NO. KODE',array()),
		                                         array("KELOMPOK UMUR",array()),
		                                         array('LAKI-LAKI',array()),
		                                         array('PEREMPUAN',array()),
		                                         array('JUMLAH',array())
	 	                                        )
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu08_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS DAN PUS PESERTA KB USIA 45-49</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu08($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array()),
		                                          array("KELOMPOK UMUR",array()),
		                                          array('JUMLAH PUS',array()),
		                                          array('PUS PESERTA KB',array()),
		                                          array('%',array())
		                                        )
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu09_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA WAJIB BELAJAR MENURUT KELOMPOK UMUR, DAN STATUS BERSEKOLAH</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu09($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_edulvl = new dt_edu_lvl;
		$nmedulvl=$dt_edulvl->getnm('Kd_edu!=0'); 
		$numrows=$dt_edulvl->getnumrows();	        
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'2')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                          array('TIDAK SEKOLAH',array('rowspan'=>'2')),
		                                          array('BERSEKOLAH',array('colspan'=>($numrows+1))),
		                                          array('JUMLAH',array('rowspan'=>'2'))
		                                        ),
		                                   $nmedulvl
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu010_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA WAJIB BELAJAR MENURUT KELOMPOK UMUR, JENIS KELAMIN DAN STATUS BERSEKOLAH</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu010($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','PEREMPUAN','JUMLAH'));
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											     array('NO. KODE',array('rowspan'=>'2')),
		                                         array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                         array('TIDAK SEKOLAH',array('colspan'=>'3')),
		                                         array('BERSEKOLAH',array('colspan'=>'3')),
		                                         array('JUMLAH',array('rowspan'=>'2'))
		                                        ),
		                                   $dt_ulang 
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu011_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA MENURUT KELOMPOK UMUR DAN PENDIDIKAN</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu011($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];

		$dt_edulvl = new dt_edu_lvl;
		$nmedulvl=$dt_edulvl->getnm('Kd_edu!=0');
		$numrows=$dt_edulvl->getnumrows();		        
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'2')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                          array('TIDAK SEKOLAH',array('rowspan'=>'2')),
		                                          array('BERSEKOLAH',array('colspan'=>($numrows+1))),
		                                          array('JUMLAH',array('rowspan'=>'2'))
		                                        ),
		                                   $nmedulvl
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu012_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA KERJA MENURUT KELOMPOK UMUR DAN JENIS PEKERJAAN</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu012($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_empmnt = new dt_empmnt_stat;
		$empmnt = $dt_empmnt->getnm('Kd_emp!=6');  
		$numrows=$dt_empmnt->getnumrows();

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'2')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                          array('TIDAK BEKERJA',array('rowspan'=>'2')), 
		                                          array('BEKERJA',array('colspan'=>($numrows+1))),
		                                          array('JUMLAH',array('rowspan'=>'2'))),                                          
		                                   $empmnt
										 ),
		                           $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu013_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KEPALA KELUARGA MENURUT KELOMPOK UMUR, KELAMIN, STATUS TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu013($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                           array(
									      array(
											    array('NO. KODE',array('rowspan'=>'2')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                        array('JENIS KELAMIN',array('colspan'=>'2')), 
		                                        array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5')),
		                                        array('JUMLAH',array('rowspan'=>'2'))
												),                                          
		                                  array( 
											    array('LAKI-LAKI',array()),
		                                        array("PEREMPUAN",array()),
		                                        array('PRA S',array()), 
		                                        array('KS I',array()),
		                                        array('KS II',array()),
		                                        array('KS III',array()),
		                                        array('KS III+',array())
		                                  )
		                               ),
		                           $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu014_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA USIA KERJA MENURUT KELOMPOK UMUR, KELAMIN, STATUS BEKERJA DAN TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu014($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];		

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'2')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                          array('JENIS KELAMIN',array('colspan'=>'2')), 
		                                          array('STATUS BEKERJA',array('colspan'=>'2')),
		                                          array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5')),
		                                          array('JUMLAH',array('rowspan'=>'2'))
												),                                          
		                                   array(
											      array('LAKI-LAKI',array()),
		                                          array("PEREMPUAN",array()),
		                                          array('BEKERJA',array()),
		                                          array("TIDAK BEKERJA",array()),
		                                          array('PRA S',array()), 
		                                          array('KS I',array()),
		                                          array('KS II',array()),
		                                          array('KS III',array()),
		                                          array('KS III+',array())
		                                         )
		                                 ),
		                            $dt_tb,$txt);
		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu015_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KEPALA KELUARGA MENURUT KELOMPOK UMUR STATUS TAHAPAN KELUARGA SEJAHTERA DAN PENDIDIKAN</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu015($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_edulvl = new dt_edu_lvl;
		$nmedulvl=$dt_edulvl->getnm('Kd_edu!=0');
		$numrows=$dt_edulvl->getnumrows();

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'3')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'3')),
		                                          array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5')),
		                                          array('PENDIDIKAN',array('colspan'=>($numrows+2))),
		                                          array('JUMLAH',array('rowspan'=>'3'))
												),                                          
		                                   array( 
											      array('PRA S',array('rowspan'=>'2')), 
		                                          array('KS I',array('rowspan'=>'2')),
		                                          array('KS II',array('rowspan'=>'2')),
		                                          array('KS III',array('rowspan'=>'2')),
		                                          array('KS III+',array('rowspan'=>'2')),
		                                          array('TIDAK SEKOLAH',array('rowspan'=>'2')),
		                                          array('BERSEKOLAH',array('colspan'=>($numrows+1)))
		                                        ),
		                                   $nmedulvl  
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu016_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KELUARGA DENGAN ANAK BALITA MENURUT KELOMPOK UMUR, JUMLAH BALITA, KEGIATAN POSYANDU DAN STATUS TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu016($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];		

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										  array(
											    array('NO. KODE',array('rowspan'=>'2')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                        array("JUMLAH KEPALA KELUARGA",array('rowspan'=>'2')),
		                                        array("JUMLAH BALITA",array('rowspan'=>'2')),
		                                        array('POSYANDU',array('colspan'=>'2')),
		                                        array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5'))
		                                       ),                                          
		                                  array( 
											    array('IKUT',array()), 
		                                        array('TIDAK',array()),
		                                        array('PRA S',array()), 
		                                        array('KS I',array()),
		                                        array('KS II',array()),
		                                        array('KS III',array()),
		                                        array('KS III+',array())
		                                       )
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu017_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS MENURUT KELOMPOK UMUR, KESERTAAN BER-KB, TEMPAT PELAYANAN DAN TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu017($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb'];		

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										  array(
											    array('NO. KODE',array('rowspan'=>'3')),
		                                        array("KELOMPOK UMUR",array('rowspan'=>'3')),
		                                        array("JUMLAH PUS",array('rowspan'=>'3')),
		                                        array("PESERTA BER-KB",array('colspan'=>'4')),
		                                        array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5'))
		                                      ),                                          
		                                  array( 
											    array('PESERTA KB',array('colspan'=>3)), 
		                                        array('BUKAN PESERTA KB',array('rowspan'=>'2')),
		                                        array('PRA S',array('rowspan'=>'2')), 
		                                        array('KS I',array('rowspan'=>'2')),
		                                        array('KS II',array('rowspan'=>'2')),
		                                        array('KS III',array('rowspan'=>'2')),
		                                        array('KS III+',array('rowspan'=>'2'))
		                                       ),
		                                 array(
		                                       array('KLINIK PEMERINTAH',array()),
		                                       array('KLINIK SWASTA',array()),
		                                       array('JUMLAH',array())
		                                      )
		                               ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu018_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS BUKAN PESERTA KB MENURUT KELOMPOK UMUR, ALASAN TIDAK BER-KB DAN TAHAPAN KELUARGA SEJAHTERA</bold><br>$subjudul</center>";
		
		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu018($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$dt_non = new dt_non_acptr_reas;
		$nmnon=$dt_non->getnm(''); 
        $nmnon[]=array('PRA S',array());
		$nmnon[]=array('KS I',array());
		$nmnon[]=array('KS II',array());
		$nmnon[]=array('KS III',array());
		$nmnon[]=array('KS III+',array());
		$numrows=$dt_non->getnumrows();

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO. KODE',array('rowspan'=>'2')),
		                                          array("KELOMPOK UMUR",array('rowspan'=>'2')),
		                                          array("ALASAN TIDAK BER-KB",array('colspan'=>($numrows+1))),
		                                          array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'5'))
		                                        ),                                          
		                                   $nmnon
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu101_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KEPALA KELUARGA DAN JUMLAH JIWA DALAM KELUARGA MENURUT JENIS KELAMIN</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu101($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(13);

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','%','PEREMPUAN','%','TOTAL')); 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH KEPALA KELUARGA",array('colspan'=>'5')),
		                                          array("JUMLAH JIWA DALAM KELUARGA",array('colspan'=>'5')),
		                                          array('RATA-2 JUMLAH JIWA PERKELUARGA',array('rowspan'=>'2'))
		                                        ),                                          
		                                    $dt_ulang,
		                                    $nocol,
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu102_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA DALAM KELUARGA, BAYI USIA 0 -< 1 TH DAN PROXY CBR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu102($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(9);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										   array(
											      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH JIWA (PENDUDUK)",array('rowspan'=>'2')),
		                                          array("JUMLAH BAYI 0 - < 1 TAHUN",array('colspan'=>'5')),
		                                          array('JUMLAH BAYI 0 - < 1 TH PER 1000 PENDUDUK (PROXY CBR)',array('rowspan'=>'2'))
		                                        ),                                          
		                                   array(
											      array('IKUT POSYANDU',array()),
		                                          array("%",array()),
		                                          array("TIDAK IKUT POSYANDU",array()),
		                                          array('%',array()),
		                                          array('TOTAL',array())
		                                        ),
		                                   $nocol,
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu103_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH WANITA USIA SUBUR, BALITA USIA 0 - < 5 TH  DAN PROXY CWR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu103($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(9);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										  array(
											    array('NO',array('rowspan'=>'2')),
		                                        array($nmklm,array('rowspan'=>'2')),
		                                        array("JUMLAH WANITA USIA SUBUR (WUS 15-49)",array('rowspan'=>'2')),
		                                        array("JUMLAH ANAK BALITA 0 - < 5 TAHUN",array('colspan'=>'5')),
		                                        array('JUMLAH BAYI 0 - < 5 TH PER WUS (PROXY CWR)',array('rowspan'=>'2'))
		                                       ),                                          
		                                  array(
											    array('IKUT POSYANDU',array()),
		                                        array("%",array()),
		                                        array("TIDAK IKUT POSYANDU",array()),
		                                        array('%',array()),
		                                        array('TOTAL',array())
		                                       ),
		                                  $nocol,
		                            ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu104_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA ANGGOTA KELUARGA MENURUT KELOMPOK UMUR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu104($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(18);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
										  array(
											     array('NO',array('rowspan'=>'2')),
		                                         array($nmklm,array('rowspan'=>'2')),
		                                         array("JUMLAH JIWA ANGGOTA KELUARGA MENURUT KELOMPOK UMUR",array('colspan'=>'15')),
		                                         array("% PERSEBARAN PER",array('rowspan'=>'2'))
		                                       ),                                          
		                                  array(
											     array('0 - < 1 TAHUN',array()),
		                                         array("%",array()),
		                                         array("1 - < 5 TAHUN",array()),
		                                         array('%',array()),
		                                         array("5 - < 6 TAHUN",array()),
		                                         array('%',array()),
		                                         array("7 - < 15 TAHUN",array()),
		                                         array('%',array()),
		                                         array("16 - < 21 TAHUN",array()),
		                                         array('%',array()),
		                                         array("22 - < 59 TAHUN",array()),
		                                         array('%',array()),
		                                         array("60 TAHUN+",array()),
		                                         array('%',array()),
		                                         array('TOTAL',array())
		                                         ),
		                                  $nocol,
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu105_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH USIA ANAK SEKOLAH, YANG SEKOLAH DAN TIDAK SEKOLAH MENURUT JENIS KELAMIN</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu105($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(19);

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','%','PEREMPUAN','%','TOTAL','%'));
		$dt_ulang[] = array('LAKI-LAKI',array());
		$dt_ulang[] = array("%",array());
        $dt_ulang[] = array("PEREMPUAN",array());
		$dt_ulang[] = array("%",array());
		$dt_ulang[] = array("TOTAL",array());

		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	     array('NO',array('rowspan'=>'3')),
		                                         array($nmklm,array('rowspan'=>'3')),
		                                         array("JUMLAH JIWA MENURUT KELOMPOK UMUR 7-15 TAHUN",array('colspan'=>'17'))
		                                         ),                                          
		                                   array(
		                                   	     array('SEKOLAH',array('colspan'=>'6')),
		                                         array("TIDAK SEKOLAH",array('colspan'=>'6')),
		                                         array("TOTAL",array('colspan'=>'6'))
		                                         ),
		                                    $dt_ulang,
		                                    $nocol,
		                                ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu106_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PASANGAN USIA SUBUR (PUS) DAN PESERTA KB MENURUT METODE KONTRASEPSI</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu106($idkec,$iddesa,$iddusun,$idrt);
		
		$db_contr = new dt_contr_typ;
		$nmcontyp = $db_contr->getnm('',0,1,1);
		$numrows=$db_contr->getnumrows();

		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm,'KEL. PRASEJAHTERA<br>% THD. TOTAL KEL.','KEL. SEJAHTERA I<br>% THD. TOTAL KEL.'));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$nocol=$this->build_nocol(21); 

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH PUS",array('rowspan'=>'2')),
		                                          array("JUMLAH PESERTA KB MENURUT METODE KONTRASEPSI",array('colspan'=>(($numrows*2)+1))),
		                                          array("% PREV KB TOTAL",array('rowspan'=>'2'))
		                                        ),                                          
		                                   $nmcontyp,
		                                   $nocol,
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu107_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KEPALA KELUARGA PRASEJAHTERA MENURUT INDIKATOR YANG JATUH</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu107($idkec,$iddesa,$iddusun,$idrt);
		
		$dt_kondks = new dt_indikator_ks;		
		$nmkondks = $dt_kondks->getnm('id_ind_ks_idk=1',0,0,1);
		$numrows=$dt_kondks->getnumrows()*2;

		$nocols=$this->build_nocol(3+$numrows);		 

		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH KELUARGA PRA SEJAHTERA",array('rowspan'=>'2')),
		                                          array("JUMLAH KEPALA KELUARGA PRASEJAHTERA MENURUT INDIKATOR",array('colspan'=>($numrows*2)))
		                                        ),                                          
		                                   $nmkondks,
		                                   $nocols,
		                                 ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu111_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH KEPALA KELUARGA DAN JUMLAH JIWA DALAM KELUARGA MENURUT JENIS KELAMIN</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu111($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(13);

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','%','PEREMPUAN','%','TOTAL'));
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	     array('NO',array('rowspan'=>'2')),
		                                         array($nmklm,array('rowspan'=>'2')),
		                                         array("JUMLAH KEPALA KELUARGA",array('colspan'=>'5')),
		                                         array("JUMLAH JIWA DALAM KELUARGA",array('colspan'=>'5')),
		                                         array('RATA-2 JUMLAH JIWA PERKELUARGA',array('rowspan'=>'2'))
		                                        ),                                          
		                                   $dt_ulang,
		                                   $nocol,
		                            ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu112_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA DALAM KELUARGA, BAYI USIA 0 -< 1 TH DAN PROXY CBR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu112($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(9);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	  array(
		                            	  	    array('NO',array('rowspan'=>'2')),
		                                        array($nmklm,array('rowspan'=>'2')),
		                                        array("JUMLAH JIWA (PENDUDUK)",array('rowspan'=>'2')),
		                                        array("JUMLAH BAYI 0 - < 1 TAHUN",array('colspan'=>'5')),
		                                        array('JUMLAH BAYI 0 - < 1 TH PER 1000 PENDUDUK (PROXY CBR)',array('rowspan'=>'2'))
		                                       ),                                          
		                                  array(
		                                  	    array('IKUT POSYANDU',array()),
		                                        array("%",array()),
		                                        array("TIDAK IKUT POSYANDU",array()),
		                                        array('%',array()),
		                                        array('TOTAL',array())
		                                       ),
		                                  $nocol,
		                            ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu113_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH WANITA USIA SUBUR, BALITA USIA 0 - < 5 TH  DAN PROXY CWR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu113($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(9);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH WANITA USIA SUBUR (WUS 15-49)",array('rowspan'=>'2')),
		                                          array("JUMLAH ANAK BALITA 0 - < 5 TAHUN",array('colspan'=>'5')),
		                                          array('JUMLAH BAYI 0 - < 5 TH PER WUS (PROXY CWR)',array('rowspan'=>'2'))
		                                        ),                                          
		                                   array(
		                                   	      array('IKUT POSYANDU',array()),
		                                          array("%",array()),
		                                          array("TIDAK IKUT POSYANDU",array()),
		                                          array('%',array()),
		                                          array('TOTAL',array())
		                                        ),
		                                   $nocol,
		                            ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu114_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA ANGGOTA KELUARGA MENURUT KELOMPOK UMUR</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu114($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(18);
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH JIWA ANGGOTA KELUARGA MENURUT KELOMPOK UMUR",array('colspan'=>'15')),
		                                          array("% PERSEBARAN PER TAHAPAN KS - ",array('rowspan'=>'2'))
	 	                                        ),                                          
		                                   array(
		                                   	       array('0 - < 1 TAHUN',array()),
		                                           array("%",array()),
		                                           array("1 - < 5 TAHUN",array()),
		                                           array('%',array()),
		                                           array("5 - < 6 TAHUN",array()),
		                                           array('%',array()),
		                                           array("7 - < 15 TAHUN",array()),
		                                           array('%',array()),
		                                           array("16 - < 21 TAHUN",array()),
		                                           array('%',array()),
		                                           array("22 - < 59 TAHUN",array()),
		                                           array('%',array()),
		                                           array("60 TAHUN+",array()),
		                                           array('%',array()),
		                                           array('TOTAL',array())
		                                         ),
		                                   $nocol,
		                           ),
		                          $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu115_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH USIA ANAK SEKOLAH, YANG SEKOLAH DAN TIDAK SEKOLAH MENURUT JENIS KELAMIN</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu115($idkec,$iddesa,$iddusun,$idrt);
		
		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(19);

		$dt_ulang = $this->dt_berulang(2,array('LAKI-LAKI','%','PEREMPUAN','%','TOTAL','%'));
		$dt_ulang[] = array('LAKI-LAKI',array());
		$dt_ulang[] = array("%",array());
        $dt_ulang[] = array("PEREMPUAN",array());
		$dt_ulang[] = array("%",array());
		$dt_ulang[] = array("TOTAL",array());
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	     array('NO',array('rowspan'=>'3')),
		                                         array($nmklm,array('rowspan'=>'3')),
		                                         array("JUMLAH JIWA MENURUT KELOMPOK UMUR 7-15 TAHUN",array('colspan'=>'17'))
		                                        ),                                          
		                                   array(
		                                   	      array('SEKOLAH',array('colspan'=>'6')),
		                                          array("TIDAK SEKOLAH",array('colspan'=>'6')),
		                                          array("TOTAL",array('colspan'=>'6'))
		                                        ),
		                                    $dt_ulang,
		                                    $nocol,
		                                ),
		                                $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu116_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PASANGAN USIA SUBUR (PUS) DAN PESERTA KB MENURUT METODE KONTRASEPSI</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu116($idkec,$iddesa,$iddusun,$idrt);
		
		$dt_contr = new dt_contr_typ;
		$nmcontyp = $dt_contr->getnm('',0,1,1);
		$numrows  = $dt_contr->getnumrows(); 

		$nm = $this->getfooternmklm($idkec,$iddesa,$iddusun,$idrt);
		$tmp = $this->build_dt_tb($tmp_dt_tb,array($nm));
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(21);       

		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array("JUMLAH PUS",array('rowspan'=>'2')),
		                                          array("JUMLAH PESERTA KB MENURUT METODE KONTRASEPSI",array('colspan'=>(($numrows*2)+1))),
		                                          array("% PREV KB TOTAL",array('rowspan'=>'2'))
		                                        ),                                          
		                                   $nmcontyp,
		                                   $nocol
		                            ),
		                           $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu21_hslfilter($idkec,$iddesa,$iddusun,$idrt,$ks){
		
		$nmks=array('pra_s'=>'PRAS S','ks_1'=>'KS I','ks_2'=>'KS II','ks_3'=>'KS III','ks_3_p'=>'KS III+'); 

		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>STATUS KERJA KEPALA KELUARGA BERDASARKAN TAHAPAN KELUARGA $nmks[$ks]</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu21($idkec,$iddesa,$iddusun,$idrt,$ks);

		$dt_empmnt = new dt_empmnt_stat;
		$empmnt= $dt_empmnt->getnm('Kd_emp!=6');
		$numrows=$dt_empmnt->getnumrows();
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                             array(
		                             	    array(
		                             	    	   array('NO. KODE',array('rowspan'=>'3')),
		                                           array($nmklm,array('rowspan'=>'3')),
		                                           array('JENIS PEKERJAAN',array('colspan'=>($numrows+2))),
		                                           array('JUMLAH',array('rowspan'=>'3'))
		                                         ),
		                                    array(
		                                    	   array('BEKERJA',array('colspan'=>($numrows+1))),
		                                           array('TIDAK BEKERJA',array('rowspan'=>'2'))
		                                         ),
		                                    $empmnt),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu22_hslfilter($idkec,$iddesa,$iddusun,$idrt,$ks,$cmbumur,$dtumur,$edu){
		
		$nmks=array('pra_s'=>'PRAS S','ks_1'=>'KS I','ks_2'=>'KS II','ks_3'=>'KS III','ks_3_p'=>'KS III+'); 
		
		switch($cmbumur)
		{
		case 1 : $umur = 'SAMA DENGAN '.$dtumur[0].' TAHUN' ;break;
		case 2 : $umur = 'KECIL DARI '.$dtumur[0].' TAHUN' ;break;
		case 3 : $umur = 'BESAR DARI '.$dtumur[0].' TAHUN' ;break;
		case 4 : $umur = $dtumur[0].' - '.$dtumur[1].' TAHUN' ;break; 
		}
		
		$str='';
		foreach ($edu as $row) {
			$str = ($str==''? $str : $str.'OR') . " Kd_edu=$row ";
		}

		$tb = new tb_gen('dbo_edu_lvl');
		$data = $tb->getData($str);
		
		$nmedu='';
		if(!empty($data))
		{
			foreach($data as $row)
			{
				$nmedu = ($nmedu==''? $nmedu : $nmedu.',') .strtoupper($row['Nm_edu_ind']);
			}
		}

		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>STATUS KERJA INDIVIDU BERDASARKAN TAHAPAN KELUARGA $nmks[$ks] UMUR $umur<BR>PENDIDIKAN $nmedu </bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu22($idkec,$iddesa,$iddusun,$idrt,$ks,$cmbumur,$dtumur,$edu);

		$dt_empmnt = new dt_empmnt_stat;
		$empmnt = $dt_empmnt->getnm('Kd_emp!=6');
		$numrows=$dt_empmnt->getnumrows();
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO. KODE',array('rowspan'=>'3')),
		                                          array($nmklm,array('rowspan'=>'3')),
		                                          array('JENIS PEKERJAAN',array('colspan'=>($numrows+2))),
		                                          array('JUMLAH',array('rowspan'=>'3'))
		                                         ),
		                                   array(
		                                   	     array('BEKERJA',array('colspan'=>($numrows+1))),
		                                         array('TIDAK BEKERJA',array('rowspan'=>'2'))
		                                         ),
		                                    $empmnt),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu3_hslfilter($idkec,$iddesa,$iddusun,$idrt,$ks){
		
		$nmks=array('pra_s'=>'PRAS S','ks_1'=>'KS I','ks_2'=>'KS II','ks_3'=>'KS III','ks_3_p'=>'KS III+'); 

		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS BUKAN PESERTA KB TAHAPAN KELUARGA $nmks[$ks] BERDASARKAN ALASAN</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu3($idkec,$iddesa,$iddusun,$idrt,$ks);

		$dt_acptr = new dt_non_acptr_reas;
		$empmnt = $dt_acptr->getnm('');
		$numrows=$dt_acptr->getnumrows();
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO. KODE',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array('ALASAN TIDAK BER-KB',array('colspan'=>($numrows+1)))
		                                   ),                                          
		                                   $empmnt),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	}

	function menu4_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH JIWA MENURUT KELOMPOK BALITA, REMAJA DAN LANSIA</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu4($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(11);

		$dt_ulang = $this->dt_berulang(4,array('JUMLAH','%'));
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO. KODE',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array('JUMLAH JIWA',array('rowspan'=>'2')),
		                                          array('BALITA (0 - < 5 TAHUN)',array('colspan'=>'2')),
		                                          array('REMAJA (16 - 24 TAHUN)',array('colspan'=>'2')),
		                                          array('LANSIA (60+ TAHUN)',array('colspan'=>'2')),
		                                          array('BALITA+REMAJA+LANSIA',array('colspan'=>'2'))
		                                        ),                                          
		                                   $dt_ulang,
		                                   $nocol
		                            ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

	function menu5_hslfilter($idkec,$iddesa,$iddusun,$idrt){
		
		$subjudul=$this->getsubjudul($idkec,$iddesa,$iddusun,$idrt);
		$html_txt = "<center><bold>JUMLAH PUS, PESERTA KB DAN BUKAN PESERTA KB</bold><br>$subjudul</center>";
		
		$nmklm = $this->getnmklm($idkec,$iddesa,$iddusun,$idrt);

		$dt_tbkep = new dt_tbkependudukan;   
		$tmp_dt_tb = $dt_tbkep->getdtmenu5($idkec,$iddesa,$iddusun,$idrt);
		
		$tmp = $this->build_dt_tb($tmp_dt_tb);
		$dt_tb = $tmp['dt_tb'];
		$txt = $tmp['footer_tb']; 

		$nocol=$this->build_nocol(7);

		$dt_ulang = $this->dt_berulang(2,array('JUMLAH','%'));
		
		$tb_hslfilter = new mytable($this->tb_header,
		                            array(
		                            	   array(
		                            	   	      array('NO. KODE',array('rowspan'=>'2')),
		                                          array($nmklm,array('rowspan'=>'2')),
		                                          array('JUMLAH PUS',array('rowspan'=>'2')),
		                                          array('PESERTA KB',array('colspan'=>'2')),
		                                          array('BUKAN PESERTA KB',array('colspan'=>'2'))
		                                        ),                                          
		                                   $dt_ulang,
		                                   $nocol
		                             ),
		                            $dt_tb,$txt);

		$html_txt .= $tb_hslfilter->display();
		return $html_txt; 
	} 

}

?>