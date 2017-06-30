<?php require_once('shared.php');
     
class dt_poll
{

  private $tb_;
   
   function __construct() {
	 
	  $tb = new tb_gen('tbgen');     
     $isviewexist = $tb->isviewexist('vw_subpoll');
     if(!$isviewexist)
     {
       $tb->createview('vw_subpoll',"SELECT kd_fam, GROUP_CONCAT(IF((kd_prospinstat = 1),id_ind_ks,NULL) SEPARATOR ',') AS kond1,  GROUP_CONCAT(IF((kd_prospinstat > 1),id_ind_ks,NULL) SEPARATOR ',') AS kond0 FROM dbo_fam_ind_detail GROUP BY Kd_fam ORDER BY id_ind_ks");
     }

     $isviewexist = $tb->isviewexist('vw_poll');
     if(!$isviewexist)
     {
       $tb->createview('vw_poll',"SELECT  a.kd_fam,a.kond1,a.kond0,c.kd_prop,c.kd_dist,c.kd_subdist,c.kd_vill,c.kd_subvill,c.kd_neigh 
FROM ((vw_subpoll a JOIN dbo_individu b ON ((a.kd_fam = b.Kd_fam))) JOIN dbo_family c ON ((a.kd_fam = c.Kd_fam)))
WHERE (ISNULL(b.Kd_mutasi) AND (b.Kd_fammbrtyp = 1))");
     }

     $this->tb_ = new tb_gen('vw_poll');

  }

  private function build_where($data,$where)
   {
      
      $kond1 = array();
      $kond0 = array();
            if(!empty($data))
            {
               foreach ($data as $key => $value) {
                 
                 if($value == 1)
                 {
                   $kond1[]=$key;
                 }else{
                   $kond0[]=$key;
                 }                 
               
               }  
            }
      
      if(!empty($kond1) and !empty($kond0)){      
           
           $kond_str1 = implode('%',$kond1); 
           
           $temp_kond_str0='';
           foreach($kond0 as $row)
           {
             $temp_kond_str0.= $temp_kond_str0=='' ? "(kond1 like '%".$row."%')" :" or (kond1 like '%".$row."%')" ;
           } 

           $kond_str0.= "($temp_kond_str0) And ";
                         
           $temp_kond_str0='';              
           foreach($kond0 as $row)
           {
             $temp_kond_str0.= $temp_kond_str0=='' ? "(kond0 like '%".$row."%')" :" or (kond0 like '%".$row."%')" ;
           }

           $kond_str0.= "($temp_kond_str0)";     

           $where ="($where) and (kond1 like '%".$kond_str1."%') and ($kond_str0)"; 

      }elseif(!empty($kond1))
      { $kond_str = implode('%',$kond1);
        
        $where ="($where) and (kond1 like '%$kond_str%')";

      }elseif(!empty($kond0))
      { 
         $temp_kond_str0='';
           foreach($kond0 as $row)
           {
             $temp_kond_str0.= $temp_kond_str0=='' ? "(kond1 like '%".$row."%')" :" or (kond1 like '%".$row."%')" ;
           } 

           $kond_str0.= "($temp_kond_str0) And ";
                         
           $temp_kond_str0='';              
           foreach($kond0 as $row)
           {
             $temp_kond_str0.= $temp_kond_str0=='' ? "(kond0 like '%".$row."%')" :" or (kond0 like '%".$row."%')" ;
           }

           $kond_str0.= "($temp_kond_str0)";     

           $where ="($where) and ($kond_str0)";         
      }         
        return $where;
   }

   public function getdatapoll($pra=array(),$ks=array(),$ks1=array(),$select,$where,$groupby)
   {
      
      //$this->tb_->sql_select="$groupby,count(*) as jml";
      //$this->tb_->sql_groupby=$groupby;

      $where_ks1 = $this->build_where($ks1,$where);     
      $data_ks1 = $this->tb_->getData($where_ks1);       
      
      $dt_arr=array();
      if(!empty($data_ks1))
      {
        foreach($data_ks1 as $row)
        {
          if(!isset($dt_arr[$row['kd_fam']]))
          {
            $dt_arr[$row['kd_fam']]=array('group'=>$row[$groupby],'gol'=>3);
          }
        }
      }


      $where_ks = $this->build_where($ks,$where);                          
      $data_ks = $this->tb_->getData($where_ks);       
      
      if(!empty($data_ks))
      {
        foreach($data_ks as $row)
        {
          if(!isset($dt_arr[$row['kd_fam']])){
           $dt_arr[$row['kd_fam']]=array('group'=>$row[$groupby],'gol'=>2);
          }        
        }
      }      

      $where_pra = $this->build_where($pra,$where);                          
      $data_pra = $this->tb_->getData($where_pra);       
      
      if(!empty($data_pra))
      {
        foreach($data_pra as $row)
        {
          if(!isset($dt_arr[$row['kd_fam']])){
             $dt_arr[$row['kd_fam']]=array('group'=>$row[$groupby],'gol'=>1);
          }   
        }
      }
            
      $stat_arr = array();
      if(!empty($dt_arr))
      {
        foreach($dt_arr as $key=>$dt)
        {
            if($dt['gol']==3){
              
	            if (!isset($stat_arr[$dt['group']]['jmlks1'])){
	              $stat_arr[$dt['group']]['jmlks1']=1;	              
	            }else{
	              $stat_arr[$dt['group']]['jmlks1']+=1; 	
	            }

                if(!isset($stat_arr[$dt['group']]['jmlttl'])){ 
                   $stat_arr[$dt['group']]['jmlttl']=1;
                 }else{
                 	$stat_arr[$dt['group']]['jmlttl']+=1;
                 }

	        }    
	        if($dt['gol']==2){    
	            if (!isset($stat_arr[$dt['group']]['jmlks'])){
	              $stat_arr[$dt['group']]['jmlks']=1;
	            }else{
	              $stat_arr[$dt['group']]['jmlks']+=1; 	
	            }

	            if(!isset($stat_arr[$dt['group']]['jmlttl'])){ 
                   $stat_arr[$dt['group']]['jmlttl']=1;
                 }else{
                 	$stat_arr[$dt['group']]['jmlttl']+=1;
                 }
	        } 
	        if($dt['gol']==1){   
	            if (!isset($stat_arr[$dt['group']]['jmlpra'])){
	              $stat_arr[$dt['group']]['jmlpra']=1;
	            }else{
	              $stat_arr[$dt['group']]['jmlpra']+=1; 	
	            }

	            if(!isset($stat_arr[$dt['group']]['jmlttl'])){ 
                   $stat_arr[$dt['group']]['jmlttl']=1;
                 }else{
                 	$stat_arr[$dt['group']]['jmlttl']+=1;
                 }
            }
        }
      }
      
      return $stat_arr;

   }

}

?>	

