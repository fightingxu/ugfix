--jk 20080411 ����FIXIII-UGFTS����Ա��Ĭ�ϳ������ѵ�¼�������ܺ�9800
if not exists (select * from operator where oper_code = 'FIXIII')
	insert operator (oper_code ,oper_name ,if_station,if_access,pwd,status,menu_set,func_set,login_batch,node_id,specify_func_flag,login_flag,fail_number,main_func,recv_rsp_flag,recv_info_flag)
	values ('FIXIII','FIX-UGFTS����Ա','0','0','','0',REPLICATE('1',800),REPLICATE('1',800),0,0,'1','1',0,5863,'1','1')
go