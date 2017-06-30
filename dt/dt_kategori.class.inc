<?php require_once('shared.php');
     
class dt_kategori
{
   private $tb;
   private $arr_kat;
   
   function __construct() {
      $this->tb = new tb_gen('dbo_kategori');

      if (($this->tb->getfieldinfo('id_kat','Type')=='tinyint(4)') and ($this->tb->getfieldinfo('id_kat','Extra')=='auto_increment') ){
         $this->tb->create('ALTER TABLE dbo_kategori CHANGE id_kat id_kat SMALLINT(4) NOT NULL');
      }

      $this->tb->sql_select = '*';
      $this->tb->sql_orderby='Kd_prosplvl,id_ind_ks';
	    $dt = $this->tb->getData('id_kat>8');      
      
      $this->arr_kat=array();
      if(!empty($dt))
      {
      	foreach($dt as $row)
      	{
           $this->arr_kat[$row['Kd_prosplvl']][$row['id_ind_ks']]=$row['Kd_prospinstat'];
      	} 
      }

   }

   function getdata($where)
   {
     $this->tb->sql_orderby='id_kat';
     $data = $this->tb->getData($where);
     return $data;
   }

   private function getmaxidkat()
   {
   	  $this->tb->sql_select = 'max(id_kat) as no';
      $dt = $this->tb->getData('');

      return $dt[0]['no'];
   }

   function getarrkat($Kd_prosplvl,$id_ind_ks)
   {
     $tmp= $this->isexist($Kd_prosplvl,$id_ind_ks) ? $this->arr_kat[$Kd_prosplvl][$id_ind_ks] : -1;
     return $tmp;
   }


   private function isexist($Kd_prosplvl,$id_ind_ks)
   {
     return isset($this->arr_kat[$Kd_prosplvl][$id_ind_ks]);
   }   

   private function save($no,$Kd_prosplvl,$id_ind_ks,$Kd_prospinstat)
   {
   	 if($this->isexist($Kd_prosplvl,$id_ind_ks))
       {
         if($this->arr_kat[$Kd_prosplvl][$id_ind_ks]!=$Kd_prospinstat){
            $this->tb->updateRecord(array('id_ind_ks'=>$id_ind_ks,'Kd_prospinstat'=>$Kd_prospinstat,'Kd_prosplvl'=>$Kd_prosplvl)); 
         }
       }else{
            $this->tb->insertRecord(array('id_kat'=>$no,'id_ind_ks'=>$id_ind_ks,'Kd_prospinstat'=>$Kd_prospinstat,'Kd_prosplvl'=>$Kd_prosplvl));
       }
   }

   function save_kategori($data,$Kd_prosplvl)
   {
   	 $no = $this->getmaxidkat()+1;

   	 if(!empty($data))
      {
         foreach ($data as $id_ind_ks => $Kd_prospinstat) {
         	 $this->save($no++,$Kd_prosplvl,$id_ind_ks,$Kd_prospinstat);
         }
      }
   }

   function build_wherestr($data)
   {
      $where_str='';
      if(!empty($data))
      {
          $str1 = '';
          $str0 = '';
          $str01 = '';
          $tmp1 = 0;
          $tmp0 = 0;
          foreach ($data as $id_ind_ks => $Kd_prospinstat) {

          	if($Kd_prospinstat==1){
               if(($id_ind_ks-$tmp1) > 1 and !empty($str1))
               {
                 $str1 = $str1.'%';
               }
               $str1 =($str1!=''? $str1.',' : '').$id_ind_ks;
               $tmp1 = $id_ind_ks;
             }
             
             if($Kd_prospinstat==0){
               if(($id_ind_ks-$tmp0) > 1 and !empty($str0))
               {
                 $str0 = $str0.'%';
               }
               $str0 =($str0!=''? $str0.',' : '').$id_ind_ks;
               $str01 =($str01!=''? $str01.' or ' : '')."(N1 like '".'%'.$id_ind_ks.'%'."')";
               $tmp0 = $id_ind_ks;
             }
          }
           if(!empty($str1))
           {
             $where_str = "(N1 LIKE '%$str1%') and (Kd_fam like '1017%')";
           }else{
             $where_str = "(N1 not LIKE '%$str0%') AND ((N0 LIKE '%$str0%') or $str01 ) and Kd_fam like '1017%'";
           }
      }
      
      return $where_str;

   }

}