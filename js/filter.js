var menu_lvl = 0, menu_idx = 0, menu_idx1 = 0, menu_idx2 = 0, menu_idx3 = 0,menu_txt='';

function isNumberKey(evt) {
	var charCode = (evt.which) ? evt.which : evt.keyCode;
	if (charCode > 31 && (charCode < 48 || charCode > 57))
		return false;

	return true;
};

function isNumberKey1(evt) {
	var charCode = (evt.which) ? evt.which : evt.keyCode;
	if (charCode > 31 && charCode!=45 && (charCode < 48 || charCode > 57))
		return false;

	return true;
};

function cmbclick(idx) {

	$('#txtumur1').attr('disabled', 'disabled');
	$('#txtumur1').val('');
	$('#txtumur2').attr('disabled', 'disabled');
	$('#txtumur2').val('');
	$('#txtumur3').attr('disabled', 'disabled');
	$('#txtumur3').val('');
	$('#txtumur4').attr('disabled', 'disabled');
	$('#txtumur4').val('');
	$('#txtumur5').attr('disabled', 'disabled');
	$('#txtumur5').val('');

	switch (idx) {
	case 1:
		$('#txtumur1').removeAttr('disabled');
		$('#txtumur1').focus();
		break;
	case 2:
		$('#txtumur2').removeAttr('disabled');
		$('#txtumur2').focus();
		break;
	case 3:
		$('#txtumur3').removeAttr('disabled');
		$('#txtumur3').focus();
		break;
	case 4:
		$('#txtumur4').removeAttr('disabled');
		$('#txtumur4').focus();
		$('#txtumur5').removeAttr('disabled');
		break;
	}

}

function bind_cmb(data) {
	
	$("#kec").change(function () {
		var idkec = $('#kec option:selected').val();
		var data1='';
		data = "idkec=" + idkec + "&idx=7";
		if(menu_idx==1 && menu_idx1==0)
        {
           data1 = data1 + "&firstdesa=Pilih Desa/Kelurahan";
           data1 = data1 + "&firstdusun=Pilih Dusun/RW";
           data1 = data1 + "&firstrt=Pilih RT";
        }
		myajax_cmb('desa', data+data1);
		data = "idx=8";
		myajax_cmb('dusun', data+data1);
		data = "idx=9";
		myajax_cmb('rt', data+data1);
	});

	$("#desa").change(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();
		var data1='';
		var preflama='';
		var kkilama='';
		var number =0;
        var isgetkki=true;
        var isgetkak=true;

		data = "idkec=" + idkec + "&iddesa=" + iddesa + "&idx=8";
		if((menu_idx==1 && menu_idx1==0) || (menu_idx==1 && menu_idx1==1))
        {           
           data1 = data1 + "&firstdusun=Pilih Dusun/RW";
           data1 = data1 + "&firstrt=Pilih RT";

           if(iddesa!='')
           {           	
           	
           	$('#pref').val(iddesa);
           	data2 = 'action=menu&isgetkki=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
           	data2 = data2 + '&iddesa=' + iddesa;
           	           	 
           	 if(menu_idx==1 && menu_idx1==1)
           	 {
                preflama = $('#preflama').val();
                if(iddesa==preflama)
                {
                	kkilama = $('#kkilama').val();
                	$('#kki').val(kkilama.trim());
                	isgetkki=false;
                	$('#nokakakhir').show();
                } else{
                	$('#nokakakhir').hide();
                } 
           	 }

           	 if(isgetkki){   
           	    myajax_cmb('',data2,null,function(data){           	               
                   $('#kki').val(data.trim());
                });
             }
            
            data2 = 'action=menu&isgetkak=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
           	data2 = data2 + '&iddesa=' + iddesa;
           	
           	if(menu_idx==1 && menu_idx1==1)
           	 {
                if(isgetkki==false){
                	isgetkak=false;
                	$("input[id^='kaklama']").each(function(index,value){
                        number = this.id.match(/\d/g);                        
                        $('#kak'+number).val($('#kaklama'+number).val());           
                      }
                    );
                }
           	 } 	


           	     
           	   myajax_cmb('',data2,null,function(data){
                
                   if(isgetkak){  
                      $('#kak1').val(data);
                   }else{
                      $('#nokakakhir').html('No KAK Terakhir : '+data);        
                   }

                   if(isgetkki){                   	
                    var number1=parseInt(data,10);
                    $("input[id^='kaklama']").each(function(index,value){
                        number = this.id.match(/\d/g);                          
                        if(number!='1'){
                          number1=number1+1;
                          var pad = "0000000";                          
                          var result = (pad+number1).slice(-pad.length);
                          $('#kak'+number).val(result);
                        }
                      }
                    );
                   } 
               }); 
           


           } 

        }		

		myajax_cmb('dusun', data+data1);
		data = "idx=9";
		myajax_cmb('rt', data+data1);
     

	});

	$("#dusun").change(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();
		var iddusun = $('#dusun option:selected').val();
		var data1='';
        if(menu_idx==1 && menu_idx1==0)
        {          
           data1 = data1 + "&firstrt=Pilih RT";
        }  
		data = "idkec=" + idkec + "&iddesa=" + iddesa + "&iddusun=" + iddusun + "&idx=9";
		myajax_cmb('rt', data+data1);

	});
  	
    	bind_filter(); 
}

function cek_cmbumur()
{
   var isfilter = true;
   var iskosong = true;

        isfilter = $('#cmbumur:checked').length > 0;
		if (!isfilter) {
			alert('PILIH OPTION UMUR TERLEBIH DAHULU !!!');
		} else {

			switch ($('#cmbumur:checked').val()) {
			case '1':
				iskosong = $('#txtumur1').val().length === 0;
				isfilter = !iskosong;				
				break;
			case '2':
				iskosong = $('#txtumur2').val().length === 0;
				isfilter = !iskosong;				
				break;
			case '3':
				iskosong = $('#txtumur3').val().length === 0;
				isfilter = !iskosong;				
				break;
			case '4':
				iskosong = $('#txtumur4').val().length === 0;
				iskosong = $('#txtumur5').val().length === 0;				
				if ($('#txtumur4').val() > $('#txtumur5').val()) {
					isfilter = false;
					alert('FIELD KIRI TIDAK BOLEH LEBIH BESAR DARI FIELD KANAN !!!');
				}
				break;
			}
			if (iskosong) {
				alert('FIELD UMUR TIDAK BOLEH KOSONG !!!');
			}			
		}
   return isfilter;
}

function get_cmbumurdata(data)
{
          switch ($('#cmbumur:checked').val()) {
			case '1':				
				data = data + "&data1=" + $('#txtumur1').val();
				break;
			case '2':				
				data = data + "&data1=" + $('#txtumur2').val();
				break;
			case '3':			
				data = data + "&data1=" + $('#txtumur3').val();
				break;
			case '4':				
				data = data + "&data1=" + $('#txtumur4').val();
				data = data + "&data2=" + $('#txtumur5').val();				
				break;
			}			
			data = data + "&cmbumur=" + $('#cmbumur:checked').val();

	return data;			
}


function cek_filter(data) {
	var i = 1;
	var isfilter = true;
	var iskosong = true;
	var iscmbks = $('#cmbks').length > 0;
	var iscmbks1 = $('#cmbks1').length > 0;
	var iscmbumur = $('#cmbumur').length > 0;
	var iscmbedu = $("input[id^='id_edu']").length > 0;
	var iscmbkb = $('#cmbkb').length > 0;
	var iscmbkb1 = $('#cmbkb1').length > 0;
	var iscmbkerja = $('#cmbkerja').length > 0;
	var iscmbsekolah = $('#cmbsekolah').length > 0;

    

			if (iscmbks) {
				isfilter = $('#cmbks:checked').length > 0;
				if (!isfilter) {
					alert('PILIH STATUS TAHAPAN KELUARGA SEJAHTERA DAHULU !!!');
				} else {
					data = data + "&cmbks=" + $('#cmbks:checked').val();
				}
			}

	 if(iscmbks && iscmbumur && iscmbedu){
			if (iscmbks && isfilter && iscmbumur) {
				isfilter = cek_cmbumur();
				if (isfilter) {
					data = get_cmbumurdata(data);
				}
			}

			if (iscmbks && isfilter && iscmbumur && iscmbedu) {
				isfilter = $("input[id^='id_edu']:checked").length > 0;
				if (!isfilter) {
					alert('PILIH PENDIDIKAN TERLEBIH DAHULU !!!');
				} else {

					$("input[id^='id_edu']:checked").each(function (index) {
						data = data + "&edu[" + i + "]=" + $(this).val();
						i++;
					});
				}
			}

	}		

	if (iscmbkb) {
		isfilter = $('#cmbkb:checked').length > 0;
		if (!isfilter) {
			alert('PILIH STATUS KB (KB/NON KB) DAHULU !!!');
		} else {
			data = data + "&cmbkb=" + $('#cmbkb:checked').val();
		}
	}

    if(iscmbkb1 && iscmbks1){
			if (iscmbkb1) {
				isfilter = $('#cmbkb1:checked').length > 0;
				if (!isfilter) {
					alert('PILIH STATUS KB (KB/NON KB/KB & NON KB) DAHULU !!!');
				} else {
					data = data + "&cmbkb1=" + $('#cmbkb1:checked').val();
				}
			}

			if (iscmbkb1 && isfilter && iscmbks1) {
				isfilter = $('#cmbks1:checked').length > 0;
				if (!isfilter) {
					alert('PILIH STATUS PENGGUNA (UMUM/PRA S & KS I) DAHULU !!!');
				} else {
					data = data + "&cmbks1=" + $('#cmbks1:checked').val();
				}
			}
    }

    if(!iscmbks && iscmbumur && !iscmbedu){
                
                isfilter = cek_cmbumur();
				if (isfilter) {
					data = get_cmbumurdata(data);
				}

			if ( iscmbumur && isfilter && iscmbkerja) {
				isfilter = $('#cmbkerja:checked').length > 0;
				if (!isfilter) {
					alert('PILIH STATUS KERJA DAHULU !!!');
				} else {
					data = data + "&cmbkerja=" + $('#cmbkerja:checked').val();
				}
			}
				 
    }

    if ( iscmbsekolah) {
				isfilter = $('#cmbsekolah:checked').length > 0;
				if (!isfilter) {
					alert('PILIH STATUS SEKOLAH DAHULU !!!');
				} else {
					data = data + "&cmbsekolah=" + $('#cmbsekolah:checked').val();
				}
			}

	if (isfilter) {
		myajax_filter(data);
	}
}


function cari_kki(){
   
         var kki=$('#kki_cari').val();
	     if(kki!='')
		 {
            data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
            data = data + '&kki=' + kki;
            myajax_filter(data);
		 }
		 else{
		 	alert('No. Kode Keluarga Indonesia (KKI) Tidak Boleh Kosong');
		    $('#kki_cari').focus();
		 }	
}

function bind_filter() {
	$("#filter_kec").click(function () {
		var idkec = $('#kec option:selected').val();

		data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
		//data = $('input[type=hidden]').serialize() + "&" +
		//$('input:text').serialize() + "&" +
		//$(":input", oTable.fnGetNodes()).serialize();

		if (idkec != '') {
			data = data + "&idkec=" + idkec;
		}

		data = data + "&idx=1";

		cek_filter(data);
	});

	$("#view_kec").click(function () {
		var idkec = $('#kec option:selected').val();

		if (idkec != '') {
			data = "idkec=" + idkec;
		}

		data = data + "&idx=2";
		myajax_filter(data);
	});

	$("#filter_desa").click(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();

		data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;

		//data = $('input[type=hidden]').serialize() + "&" +
		//$('input:text').serialize() + "&" +
		//$(":input", oTable.fnGetNodes()).serialize();

		if (idkec != '') {
			data = data + "&idkec=" + idkec;
		}
		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		data = data + "&idx=3";

		cek_filter(data);
	});

	$("#view_desa").click(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();

		if (idkec != '') {
			data = "idkec=" + idkec;
		}
		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		data = data + "&idx=4";
		myajax_filter(data);
	});

	$("#filter_dusun").click(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();
		var iddusun = $('#dusun option:selected').val();
        var iscek = true;

		if(menu_idx==3 && menu_idx1==1)
        {
        	
        	iscek = idkec!='' && iddesa!='';
        	if(!iscek)
        	{
        		alert('PILIH KECAMATAN DAN DESA DAHULU !!!');
        	}
        }

		data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;

		//data = $('input[type=hidden]').serialize() + "&" +
		//$('input:text').serialize() + "&" +
		//$(":input", oTable.fnGetNodes()).serialize();

		if (idkec != '') {
			data = data + "&idkec=" + idkec;
		}

		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		if (iddusun != '') {
			data = data + "&iddusun=" + iddusun;
		}
		data = data + "&idx=5";

		if(iscek){
		 cek_filter(data);
        }
	});

	$("#view_dusun").click(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();
		var iddusun = $('#dusun option:selected').val();
		

		if (idkec != '') {
			data = "idkec=" + idkec;
		}

		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		if (iddusun != '') {
			data = data + "&iddusun=" + iddusun;
		}

		data = data + "&idx=6";
        
		 myajax_filter(data);
        
	});

	$("#filter_rt").click(function () {
		var idkec = $('#kec option:selected').val();
		var iddesa = $('#desa option:selected').val();
		var iddusun = $('#dusun option:selected').val();
		var idrt = $('#rt option:selected').val();
        var iscek = true;
        
        if(menu_idx==3 && menu_idx1==1)
        {
        	iscek = idkec!='' && iddesa!='';
        	if(!iscek)
        	{
        		alert('PILIH KECAMATAN DAN DESA DAHULU !!!');
        	}
        }   
		

		data = 'action=menu&isfilter=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
		//data = $('input[type=hidden]').serialize() + "&" +
		//  $('input:text').serialize() + "&" +
		//$(":input", oTable.fnGetNodes()).serialize();

		if (idkec != '') {
			data = data + "&idkec=" + idkec;
		}

		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		if (iddusun != '') {
			data = data + "&iddusun=" + iddusun;
		}

		if (idrt != '') {
			data = data + "&idrt=" + idrt;
		}

		data = data + "&idx=5";
        if(iscek){
		 cek_filter(data);
        }

	});
}

function tab_click(datatab,idkec,iddesa,iddusun,idrt)
{
	data = 'action=menu&istbclick=1&menu_lvl=' + menu_lvl + '&menu_idx=' + menu_idx + '&menu_idx1=' + menu_idx1 + '&menu_idx2=' + menu_idx2 + '&menu_idx3=' + menu_idx3;
    
        if (idkec != '') {
			data = data + "&idkec=" + idkec;
		}

		if (iddesa != '') {
			data = data + "&iddesa=" + iddesa;
		}

		if (iddusun != '') {
			data = data + "&iddusun=" + iddusun;
		}

		if (idrt != '') {
			data = data + "&idrt=" + idrt;
		}   

	tmp_txt = datatab.getAttribute('href');
	tmp_txt = tmp_txt.replace('#','');	
	idx = tmp_txt.split('-')[1];
   	data = data + "&tbidx=" + idx;
	myajax_cmb(tmp_txt,data,function(){
             $('#'+tmp_txt).html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");
   
    });	
   
}

