<?php require_once('shared.php');
     
class dt_indikator_ks
{
   private $tb_;
   function __construct() {
	$this->tb_ = new tb_gen('dbo_indikator_ks');
   }

   public function getindikator($where='')
   {
   	  $data = $this->tb_->getData($where);
   	  return $data;
   }
   
   function get_ind_ks()
   {
     $this->tb_->sql_orderby='id_ind_ks_idk,no_ind_ks';
     $data = $this->getdata('id_ind_ks>5');

     $ind_ks=array();
     if(!empty($data))
     {
       foreach ($data as $row) {
         	$ind_ks[$row['id_ind_ks']]='';
         }  
     } 

     return $ind_ks;
   }

     function getdata($where)
   {    
      $this->tb_->sql_orderby='id_ind_ks_idk,no_ind_ks';
      return $this->tb_->getData($where);
   }

   function getnumrows()
   {
   	  return $this->tb_->numrows;
   }

   function getnm($where,$isjumlah=1,$istotal=0,$isprosen=0,$attr=array())
   {
	  
	  $data = $this->getdata($where);	  
	  $tmp=array();
	  if(!empty($data)){
			foreach($data as $row)
			{
				$tmp[]=array(strtoupper($row['nm_ind_ks']),$attr);
                if($isprosen==1){
                   $tmp[]=array('%',array()); 
                 }
			}
			if($isjumlah==1){
			 $tmp[]=array('JUMLAH',array());
			} 
            if($istotal==1){
              $tmp[]=array('TOTAL',array());
            }
		}		
	  return $tmp;	
   }

   function insert_data($data)
   {
     $this->tb_->insertRecord($data);
   }

}

?>   