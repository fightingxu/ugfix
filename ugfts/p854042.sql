/*#$&B#----�ű�ת���� For SyBase	03-12-04*/
/* --------------------------------------------------------------
 * �������ƣ�p854042.sql
 * �汾��Ϣ��6.8.2.x
 * �����ܣ���ѯ���ճɽ�
 * ==============================================================

���������
          ����Ա       scust_no  oper_code varchar(10)
          ϯλ��       sserial2  seat_no   varchar(10)
          �ͻ���       sholder_ac_no cust_no varchar(16)
          �ͻ���       sserial1  cust_class char(10)
          ��Լ��       scust_auth contract_code varchar(16)
          �ϲ���־      sstatus1  bind_flag
          ���гɽ������   smain_flag done_flag
          ����        scurrency_type currency_code
          �Ƿ�����ϼ�           sum_flag char

���������
          ί�к�       lserial0
          �ͻ���       sholder_ac_no
          �ͻ�����      sname
          ���ױ���      sholder_ac_no2
          ����������     smarket_code
          Ʒ�ִ���      sstock_code
          ������       sdate1
          �ɽ���       lvol1
          �ɽ���       damt2
          ��ƽ���      sstatus3
          Ͷ�����      sstatus4
          ��������      sstatus2
          ϵͳ��       sorder0
          �ɽ���       lvol11
          �������ɽ���    sserial0
          ϯλ��       sserial2
          ����        scurrency_type
          �ɽ�ʱ��      stime3
          ������
          ����Ա      scust_no
�����߼���

ע��㣺


 * ==============================================================
 * ��������:    20031106
 * �������汾:  1.0
 * ������:      hezhenhua
 * --------------------------------------------------------------
 * �޸����ڣ�   20040205
 * �޸���Ա��   hezhenhua
 * �޸�������   ��������ͺϼƼ�¼���
 * ��ע��Ϣ     6.0.0.1
 * --------------------------------------------------------------
 * �޸����ڣ�   20040325
 * �޸���Ա��   hezhenhua
 * �޸�������   �ϼƼ�¼�����ӳɽ�����
 * ��ע��Ϣ     6.0.0.2
 * --------------------------------------------------------------
 * �޸����ڣ�   20040610
 * �޸���Ա��   hezhenhua
 * �޸�������   ���Ĳ�ѯ��������Ʒ�ִ����"like"����Ϊ"="
 * ��ע��Ϣ     6.0.0.3
 * --------------------------------------------------------------
 * �޸����ڣ�   20040728
 * �޸���Ա��   hezhenhua
 * �޸�������   �ϲ��ɽ���ʱ������������ͻ����ơ��ֶ�
 * ��ע��Ϣ     6.0.0.4
 * --------------------------------------------------------------
 * �޸����ڣ�   20040809
 * �޸���Ա��   hezhenhua
 * �޸�������   �������Ƶ²���Ա�Ĳ�ѯ��������"oper_code = @mi_oper_code"
 * ��ע��Ϣ     6.0.0.5
 * --------------------------------------------------------------
 * �޸����ڣ�   20040825
 * �޸���Ա��   hezhenhua
 * �޸�������   �����������������Ա��
 * ��ע��Ϣ     6.0.0.6
 * --------------------------------------------------------------
 * �޸����ڣ�   20041008
 * �޸���Ա��   hezhenhua
 * �޸�������   ���ݱ�����˳���������
 * ��ע��Ϣ     6.0.0.7
 * --------------------------------------------------------------
 * �޸����ڣ�   20041105
 * �޸���Ա��   wtbao
 * �޸�������   ����������ʹ�õ�order by�Ӿ��е�����entrust_no,done_no
 		��ΪĿǰ��done_no��Ŀ�ģ��ṩ���׼�ط�����ʹ�ã�ͬʱ��
 		done_no���Ǹñ�ľۼ�������
 * ��ע��Ϣ     6.0.0.8
 * --------------------------------------------------------------
 * �޸����ڣ�   20041123
 * �޸���Ա��   hezhenhua
 * �޸�������   ���������ֶΡ�sum_flag���������Ƿ�����ϼ���Ϣ��1��������������������
 * ��ע��Ϣ     6.0.0.9
 * --------------------------------------------------------------
 * �޸����ڣ�   20050322
 * �޸���Ա��   wtbao
 * �޸�������	�ںϲ���־������������һ����ܵ�����ֵ��2������Ϊ�ϲ�ͬ��ί�еı�־��
 		Ŀǰ���ֶο���������Ϊ3����0������1������2��������ֱ�Ϊ�Գɽ���¼�����κ�
 		�����ϲ�ͬ�ͻ�ͬƷ��ͬ��λ�ϲ��ɽ������ϲ�ͬһί�еķֱʳɽ���
 * ��ע��Ϣ     6.0.2.1
 * --------------------------------------------------------------
 * �޸����ڣ�   20050322
 * �޸���Ա��   wtbao
 * �޸�������	�޸�ԭ�ϼ���Ϣ�е�20���ֶ�����ɽ����ۡ���21���ֶ����''��bug��
 		����ԭ��Ӧ����ԭ������а����ɽ����ۣ����Ǻ����ѳɽ������õ��ˣ�
 		��������ֶ����Ѿ�ȥ���ˣ����������ںϼƵ����������Ӧ���޸ġ�
 		����Ӧ�÷�������Ԥ��varchar�Ͷ�ʵ�������ֵ�͵������Ϊ�գ����ϼƵĲ���Ա
 		Ҳ��ǡ��Ҳ�ǿգ���������һֱû�б����֡�
 * ��ע��Ϣ     6.0.2.2
 * --------------------------------------------------------------
 * �޸����ڣ�   20061103
 * �޸���Ա��   ����ӱ
 * �޸�������   �����Ż�,��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
 * ��ע��Ϣ     6.3.0.1
 * --------------------------------------------------------------
 * �޸����ڣ�	20061123
 * �޸���Ա��	jk
 * �޸�������	����ǿƽ��־
 * ��ע��Ϣ��	6.4.0.1
 * --------------------------------------------------------------
 * �޸����ڣ�	20081008
 * �޸���Ա��	jk
 * �޸�������	��������ʽ�Ĵ�������Ų�ѯ�Ĵ���
 * ��ע��Ϣ:	6.6.5.1
 * --------------------------------------------------------------
 * �޸����ڣ�	20100119
 * �޸���Ա��	jk
 * �޸�������	�����Ͻ��ײ�ѯ��֧��������
 * ��ע��Ϣ:	6.8.0.1
 * --------------------------------------------------------------
 * �޸����ڣ�	20100421
 * �޸���Ա��	zlm
 * �޸�������	���Ӳ�ѯ��������ƽ��������������������Ϊ�ա�0-����1-ƽ��Ĭ��Ϊ�գ���
 		�մ���ȫ����0-�������ֵ���1-ƽ����ƽ�ֵ�������ƽ���ƽ�֡�
 * ��ע��Ϣ:	6.8.2.1
 * --------------------------------------------------------------

���Խű�
EXEC p854042
           '',    --����Ա    varchar(10)
           '',    --ϯλ��    varchar(12)
           '',    --�ͻ���    varchar(15)
           '',    --�ͻ���    varchar(12)
           '',    --��Լ��    varchar(20)
           '',    --�ϲ���־    char
           '',    --���гɽ������    char
           '',     --����    char(2)
           ''
select * from cust_real_done
select * from oper_all_cust
select * from cust_basic
select * from trade_contract
 * -------------------------------------------------------------- */

if exists(select * from sysobjects where id=object_id('p854042') and  (type='P') )
        drop proc p854042
go

exec	sp_upgrade_control
	'6.8.2.1',			--�汾��
	'1',				--������־
	'p854042',			--sp���ܺ�
	''				--�޸ı�־
go

create  procedure p854042
	@mi_oper_code    varchar(10),    --����Ա
	@mi_seat_no    varchar(12),    --ϯλ��
	@mi_cust_no    varchar(15),    --�ͻ���
	@mi_cust_class    varchar(12),    --�ͻ���
	@mi_contract_code    varchar(20),    --��Լ��
	@mi_bind_flag    char,    --�ϲ���־
	@mi_done_flag    char,    --���гɽ������
	@mi_currency_code    char(2),     --����
	@mi_sum_flag	char,	--�Ƿ�����ϼ�
	@mi_order_by	char(1) = '1',	--����ʽ	20081008 6.6.5.1
	@mi_subtotal	char(1) = '0',	--�Ƿ���ҪС��	20081008 6.6.5.1
	@mi_eo_flag     char(1) = ''  	--��ƽ 20100421 6.8.2.1  �����ֵ� 80
as
begin
	declare @ocode int, @omsg varchar(80),@rowcount_var int,@if_batch char(1)

	--zlm 20100421 6.8.2.1
	declare @a varchar(5),
		@b varchar(5),
		@eo_flag varchar(5)

	if @mi_eo_flag = '0'
		select @a = '0', @b = ''
	else if @mi_eo_flag = '1'
		select @a = '1' ,@b = '3'


	DECLARE @t_exch_code	   char(1)	  ,
		@t_vari_code     varchar(8) ,
		@t_vari_name     varchar(20),
		@t_deliv_date    varchar(8)	  ,
		@t_contract_code varchar(16),
		@t_max_hold	   int        ,
		@t_hands	       int        ,
		@t_deliv_rule    char(1)	  ,
		@t_min_hand	   int	      ,
		@t_max_hand	   int

          --���������ʱ��
          create table #tmp
          (
          	entrust_no    numeric(10)     ,
          	cust_no       varchar(16)     ,
          	cust_name     varchar(8)      ,
          	tx_no         varchar(16)     ,
          	exch_code     char(1)         ,
          	vari_code     varchar(8)      ,
          	deliv_date    char(8)         ,
          	done_qty      int             ,
          	done_price    decimal(12,4)   ,
          	eo_flag       char(1)         ,
          	sh_flag       char(1)         ,
          	bs_flag       char(1)         ,
          	sys_no        varchar(16)     ,
          	done_no       int             ,
          	exch_done_no  varchar(16)     ,
          	seat_no       varchar(10)     ,
          	currency_code char(1)         ,
          	done_time     char(8)         ,
          	commi         decimal(19,4)   ,
          	oper_code     varchar(16)     ,
          	force_offset  char(1)

          )

          if @@error <> 0
          begin
          	select @ocode = -1, @omsg = '������ʱ��ʧ��'
          	goto l_fatal
          end

	create	table #tmp_cust (
		cust_no varchar(16)
		)

	select	@t_vari_name = '',
		@t_deliv_date = ''

	--20100119 �����Ͻ��ײ�ѯ��֧��������
	if @mi_seat_no = '' and @mi_cust_no <> '' and @mi_cust_class = '' and @mi_contract_code = ''
		and @mi_bind_flag = '0' and @mi_done_flag = '1' and @mi_currency_code = '1' and @mi_sum_flag = ''
		and @mi_order_by = '' and @mi_subtotal = ''
	begin
		SELECT	entrust_no   ,  --ί�к�
			cust_no      ,  --�ͻ���
			cust_name    ,  --�ͻ�����
			tx_no        ,  --���ױ���
			exch_code    ,  --����������
			vari_code    ,  --Ʒ�ִ���
			deliv_date   ,  --������
			done_qty	    ,  --�ɽ���
			done_price   ,  --�ɽ���
			eo_flag      ,  --��ƽ���
			sh_flag      ,  --Ͷ�����
			bs_flag      ,  --��������
			sys_no       ,  --ϵͳ��
			done_no      ,  --�ɽ���
			exch_done_no ,  --�������ɽ���
			seat_no      ,  --ϯλ��
			currency_code,  --����
			done_time    ,  --�ɽ�ʱ��
			frzn_commi   , 	--������
			oper_code,				--����Ա
			force_offset	--ǿƽ��־ 20061123 6.4.0.1
		FROM   cust_real_done
		WHERE  (cust_no = @mi_cust_no)
		AND	(currency_code = @mi_currency_code)
		order by done_no

/*		--20100119 ���Ͻ��ײ�Ҫ�ϼ�
		select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
		FROM   cust_real_done
		WHERE  (cust_no = @mi_cust_no)
		AND	(currency_code = @mi_currency_code)
*/
		return 0
	end

          --wtbao 20050322 ����Ĵ�����������@mi_bind_flag���з�֧������������Ϊ��0���͡�1����
          --����ԭ�е�ģʽ�������������ǡ�2��������������֧������������������򱨴�
          if (@mi_bind_flag not in ('0','1','2'))
          begin
          	select @ocode = -1, @omsg = '����Ĳ�ѯ�����ϲ���ǲ���ȷ'
          	goto l_fatal
          end

	--20081008 6.6.5.1 �ж��Ƿ���Ų�ѯ
	if substring(@mi_cust_no,1,1) = '*'
	begin
		select	@if_batch = '1'

		insert	#tmp_cust
		select	distinct cust_no
		from	batch_entrust_setting
		where	group_code = substring(@mi_cust_no,2,char_length(@mi_cust_no) - 1)
		and	oper_code = @mi_oper_code
		and	(@mi_seat_no = '' or seat_no = @mi_seat_no)

		select @ocode=@@error,@rowcount_var = @@rowcount
		if @ocode <> 0
		begin
		  	select @omsg='��ѯ����ί�����ñ����'
		      	goto l_fatal
		end

		if @rowcount_var = 0
		begin
		  	select @omsg='��������Ų�����'
		      	goto l_fatal
		end
	end
	else
	begin
		select	@if_batch = '0'
	end

          -- declare @test char(8)
          -- select @test = '1'
          --1��	�ж�����ĺ�Լ���Ƿ�Ϊ�գ����Ϊ�գ�����4������ ִ��2
          IF @mi_contract_code <> ''
          BEGIN
          	--select @test = '2'
          	--2��	��ֺ�Լ��ΪƷ�ִ���+������

          	EXEC    get_variety_info @mi_contract_code         ,
                                	@t_exch_code	   output ,
                                	@t_vari_code       output ,
                                	@t_vari_name       output ,
                                	@t_deliv_date      output ,
                                	@t_contract_code   output ,
                                	@t_max_hold	       output ,
                                	@t_hands	       output ,
                                	@t_deliv_rule      output ,
                                	@t_min_hand	       output ,
                                	@t_max_hand	       output ,
                                	@ocode             output ,
                                	@omsg              output
          	IF @ocode <> 0
          	BEGIN
              		GOTO l_fatal
          	END
          END

          --select @test = '4'
          --4���ڡ�����Ա�����в����������Ա�Ƿ����Ʊ�ǣ����û�����ƣ�ִ��5������ִ��6
          declare @t_if_access char(1)

          select @t_if_access = a.if_access
          	 from operator as a
          	 where a.oper_code = @mi_oper_code

	--20081008 6.6.5.1 ����ѯ�߼��ֳ�����͵���2�Σ�ͬʱ������Ų�ѯ�������2000��Ϊ5000���ع�~~
	if @mi_order_by = '0'
	begin
		IF @t_if_access = '0'	--û������
		BEGIN
			--5.
			--select @test = '5'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�����
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
					--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		SELECT	0   ,		--ί�к�
							cust_no      ,   --�ͻ���
							cust_name    ,          --�ͻ�����
							tx_no        ,   --���ױ���
							exch_code    ,   --����������
							vari_code    ,   --Ʒ�ִ���
							deliv_date   ,   --������
							sum(done_qty),   --�ɽ���
							done_price   ,   --�ɽ���
							eo_flag      ,   --��ƽ���
							sh_flag      ,   --Ͷ�����
							bs_flag      ,   --��������
							''       ,       --ϵͳ��
							0      ,         --�ɽ���
							'' ,             --�������ɽ���
							''      ,        --ϯλ��
							currency_code,   --����
							''    ,          --�ɽ�ʱ��
							sum(frzn_commi), 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM	cust_real_done
						WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
							if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

						if (@mi_cust_no = '')
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
							SELECT 0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
			          	end
				END
				ELSE
				BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
					if @mi_sum_flag <> '1'
					begin
						if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

					SELECT	0   ,		--ί�к�
						cust_no      ,   --�ͻ���
						cust_name    ,          --�ͻ�����
						tx_no        ,   --���ױ���
						exch_code    ,   --����������
						vari_code    ,   --Ʒ�ִ���
						deliv_date   ,   --������
						sum(done_qty),   --�ɽ���
						done_price   ,   --�ɽ���
						eo_flag      ,   --��ƽ���
						sh_flag      ,   --Ͷ�����
						bs_flag      ,   --��������
						''       ,       --ϵͳ��
						0      ,         --�ɽ���
						'' ,             --�������ɽ���
						''      ,        --ϯλ��
						currency_code,   --����
						''    ,          --�ɽ�ʱ��
						sum(frzn_commi), 	--������
						oper_code,				--����Ա
						force_offset	--ǿƽ��־ 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							FROM   cust_basic
							WHERE  cust_class LIKE @mi_cust_class)
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
				END
			END
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '0'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ��
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--��������� = '' or currency_code = ������֣�
				--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
						begin
							if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT	entrust_no   ,  --ί�к�
							cust_no      ,  --�ͻ���
							cust_name    ,  --�ͻ�����
							tx_no        ,  --���ױ���
							exch_code    ,  --����������
							vari_code    ,  --Ʒ�ִ���
							deliv_date   ,  --������
							done_qty	    ,  --�ɽ���
							done_price   ,  --�ɽ���
							eo_flag      ,  --��ƽ���
							sh_flag      ,  --Ͷ�����
							bs_flag      ,  --��������
							sys_no       ,  --ϵͳ��
							done_no      ,  --�ɽ���
							exch_done_no ,  --�������ɽ���
							seat_no      ,  --ϯλ��
							currency_code,  --����
							done_time    ,  --�ɽ�ʱ��
							frzn_commi   , 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						order by done_no desc
					end
					else
					begin
						if @mi_sum_flag <> '1'
						begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end

			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

						if (@mi_cust_no = '')
						begin
							SELECT	entrust_no   ,  --ί�к�
								cust_no      ,  --�ͻ���
								cust_name    ,  --�ͻ�����
								tx_no        ,  --���ױ���
								exch_code    ,  --����������
								vari_code    ,  --Ʒ�ִ���
								deliv_date   ,  --������
								done_qty	    ,  --�ɽ���
								done_price   ,  --�ɽ���
								eo_flag      ,  --��ƽ���
								sh_flag      ,  --Ͷ�����
								bs_flag      ,  --��������
								sys_no       ,  --ϵͳ��
								done_no      ,  --�ɽ���
								exch_done_no ,  --�������ɽ���
								seat_no      ,  --ϯλ��
								currency_code,  --����
								done_time    ,  --�ɽ�ʱ��
								frzn_commi   , 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							order by done_no desc
						end
						else
						begin
							SELECT	entrust_no   ,  --ί�к�
								cust_no      ,  --�ͻ���
								cust_name    ,  --�ͻ�����
								tx_no        ,  --���ױ���
								exch_code    ,  --����������
								vari_code    ,  --Ʒ�ִ���
								deliv_date   ,  --������
								done_qty	    ,  --�ɽ���
								done_price   ,  --�ɽ���
								eo_flag      ,  --��ƽ���
								sh_flag      ,  --Ͷ�����
								bs_flag      ,  --��������
								sys_no       ,  --ϵͳ��
								done_no      ,  --�ɽ���
								exch_done_no ,  --�������ɽ���
								seat_no      ,  --ϯλ��
								currency_code,  --����
								done_time    ,  --�ɽ�ʱ��
								frzn_commi   , 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							order by done_no desc
		        			end
			          	end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ��
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no desc

				END
			END
			ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and ������Ա = �������Ա����
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
				--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT	0   ,		--ί�к�
							cust_no      ,   --�ͻ���
							cust_name    ,          --�ͻ�����
							tx_no        ,   --���ױ���
							exch_code    ,   --����������
							vari_code    ,   --Ʒ�ִ���
							deliv_date   ,   --������
							sum(done_qty),   --�ɽ���
							done_price   ,   --�ɽ���
							eo_flag      ,   --��ƽ���
							sh_flag      ,   --Ͷ�����
							bs_flag      ,   --��������
							''       ,       --ϵͳ��
							0      ,         --�ɽ���
							'' ,             --�������ɽ���
							''      ,        --ϯλ��
							currency_code,   --����
							''    ,          --�ɽ�ʱ��
							sum(frzn_commi), 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	oper_code = @mi_oper_code
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
									select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

						if (@mi_cust_no = '')
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			end
			          	end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--and ������Ա = �������Ա����
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	oper_code = @mi_oper_code
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
				END
			END
			ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '0'
			BEGIN
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and ������Ա = �������Ա��
	          		--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          		--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
		          		  	end

		          		  	if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no desc
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          		  	end

		          		  	if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			if (@mi_cust_no = '')
		          			begin
			          			SELECT entrust_no   ,  --ί�к�
			          			       cust_no      ,  --�ͻ���
			          			       cust_name    ,  --�ͻ�����
			          			       tx_no        ,  --���ױ���
			          			       exch_code    ,  --����������
			          			       vari_code    ,  --Ʒ�ִ���
			          			       deliv_date   ,  --������
			          			       done_qty	    ,  --�ɽ���
			          			       done_price   ,  --�ɽ���
			          			       eo_flag      ,  --��ƽ���
			          			       sh_flag      ,  --Ͷ�����
			          			       bs_flag      ,  --��������
			          			       sys_no       ,  --ϵͳ��
			          			       done_no      ,  --�ɽ���
			          			       exch_done_no ,  --�������ɽ���
			          			       seat_no      ,  --ϯλ��
			          			       currency_code,  --����
			          			       done_time    ,  --�ɽ�ʱ��
			          			       frzn_commi   , 	--������
			          			       oper_code,				--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			order by done_no desc
		          			end
		          			else
		          			begin
			          			SELECT entrust_no   ,  --ί�к�
			          			       cust_no      ,  --�ͻ���
			          			       cust_name    ,  --�ͻ�����
			          			       tx_no        ,  --���ױ���
			          			       exch_code    ,  --����������
			          			       vari_code    ,  --Ʒ�ִ���
			          			       deliv_date   ,  --������
			          			       done_qty	    ,  --�ɽ���
			          			       done_price   ,  --�ɽ���
			          			       eo_flag      ,  --��ƽ���
			          			       sh_flag      ,  --Ͷ�����
			          			       bs_flag      ,  --��������
			          			       sys_no       ,  --ϵͳ��
			          			       done_no      ,  --�ɽ���
			          			       exch_done_no ,  --�������ɽ���
			          			       seat_no      ,  --ϯλ��
			          			       currency_code,  --����
			          			       done_time    ,  --�ɽ�ʱ��
			          			       frzn_commi   , 	--������
			          			       oper_code,				--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			order by done_no desc
		          			end
					end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
				--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--and ������Ա = �������Ա��
				--��������� = '' or currency_code = ������֣�
					--insert into #tmp
					if @mi_sum_flag <> '1'
		  			begin
		  				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

					SELECT entrust_no   ,  --ί�к�
					       cust_no      ,  --�ͻ���
					       cust_name    ,  --�ͻ�����
					       tx_no        ,  --���ױ���
					       exch_code    ,  --����������
					       vari_code    ,  --Ʒ�ִ���
					       deliv_date   ,  --������
					       done_qty	    ,  --�ɽ���
					       done_price   ,  --�ɽ���
					       eo_flag      ,  --��ƽ���
					       sh_flag      ,  --Ͷ�����
					       bs_flag      ,  --��������
					       sys_no       ,  --ϵͳ��
					       done_no      ,  --�ɽ���
					       exch_done_no ,  --�������ɽ���
					       seat_no      ,  --ϯλ��
					       currency_code,  --����
					       done_time    ,  --�ɽ�ʱ��
					       frzn_commi   , 	--������
					       oper_code,				--����Ա
					       force_offset	--ǿƽ��־ 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							    FROM   cust_basic
							    WHERE  cust_class LIKE @mi_cust_class)
					AND	oper_code = @mi_oper_code
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				       	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					order by done_no desc
		          	END
			end
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '2'
			begin
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          			--insert into #tmp
					--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

						if (@mi_cust_no = '')
						begin
							SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
							SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
			          	end
				END
				ELSE
				BEGIN
					if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          		END
	          	end
	          	else IF @mi_done_flag = '0' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          			--insert into #tmp
	          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			if (@mi_cust_no = '')
		          			begin
			          			SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
			          			SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			        		end
			          	end
				END
				ELSE
				BEGIN
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	oper_code = @mi_oper_code
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          		END
	          	end
		END
		ELSE IF @t_if_access = '1'	--������
		BEGIN
		--6.
			--select @test = '6'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
						--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
						EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
						IF @ocode <> 0
						BEGIN
							GOTO l_fatal
						END
						--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
						--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
						--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
						--and ���ͻ��� = ����ͻ��ţ�
						--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)��
						--��������� = '' or currency_code = ������֣�
						--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          			--and    oper_code = @mi_oper_code
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          			--and    oper_code = @mi_oper_code
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ����
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          		END
			END
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '0'
			BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no desc
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
		          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--��������� = '' or currency_code = ������֣�
		          			--insert into #tmp
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          			--and    oper_code = @mi_oper_code
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          			--and    oper_code = @mi_oper_code
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			--and    oper_code = @mi_oper_code
		          			order by done_no desc
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		          		if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			AND	bs_flag = '1'
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no desc
	          		END
	          	END
	          	ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '1'
	          	BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
		          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
		          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա����
		          		--��������� = '' or currency_code = ������֣�
		          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա����
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			and oper_code = @mi_oper_code
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          		END
	          	END
	          	ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '0'
	          	BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no desc
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
		          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա��
		          		--��������� = '' or currency_code = ������֣�
		          			--insert into #tmp
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no desc
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա��
	          		--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and    oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and    oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
	          			end

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and    oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no desc
	          		END
	          	end
	          	else IF @mi_done_flag = '1' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			--and    oper_code = @mi_oper_code
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ����
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          		END
	          	end
	          	else IF @mi_done_flag = '0' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			end
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
		          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
		          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա����
		          		--��������� = '' or currency_code = ������֣�
		          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

			          		if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա����
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
					end

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
				end	--for else
			end	--for IF @mi_done_flag = '0' AND @mi_bind_flag = '2
		end	--for IF @t_if_access = '1'
		else
		begin
			select @ocode = -2, @omsg = '����Ա�Ų����ڻ����Ա����������Ч'
			goto l_fatal
		end

	          select @ocode = @@error
	          if @ocode <> 0
	          begin
	          	select @ocode = -3, @omsg = '��ѯ�ͻ����ճɽ���ʧ��'
	          	goto l_fatal
	          end
	end
	else	--if @mi_order_by = '1'
	begin
		IF @t_if_access = '0'	--û������
		BEGIN
			--5.
			--select @test = '5'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�����
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
					--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						SELECT	0   ,		--ί�к�
							cust_no      ,   --�ͻ���
							cust_name    ,          --�ͻ�����
							tx_no        ,   --���ױ���
							exch_code    ,   --����������
							vari_code    ,   --Ʒ�ִ���
							deliv_date   ,   --������
							sum(done_qty),   --�ɽ���
							done_price   ,   --�ɽ���
							eo_flag      ,   --��ƽ���
							sh_flag      ,   --Ͷ�����
							bs_flag      ,   --��������
							''       ,       --ϵͳ��
							0      ,         --�ɽ���
							'' ,             --�������ɽ���
							''      ,        --ϯλ��
							currency_code,   --����
							''    ,          --�ɽ�ʱ��
							sum(frzn_commi), 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM	cust_real_done
						WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

						select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
						if (@mi_cust_no = '')
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
							SELECT 0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

						end
						select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			--order by done_no
		          			--select @t_vari_code, @t_deliv_date
		          			--select @test = '0,1,1,a'
		          			--����ϼƼ�¼
		          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
		          			if @mi_sum_flag <> '1'
		          			begin
							if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end
			          	end
				END
				ELSE
				BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
				--insert into #tmp
					SELECT	0   ,		--ί�к�
						cust_no      ,   --�ͻ���
						cust_name    ,          --�ͻ�����
						tx_no        ,   --���ױ���
						exch_code    ,   --����������
						vari_code    ,   --Ʒ�ִ���
						deliv_date   ,   --������
						sum(done_qty),   --�ɽ���
						done_price   ,   --�ɽ���
						eo_flag      ,   --��ƽ���
						sh_flag      ,   --Ͷ�����
						bs_flag      ,   --��������
						''       ,       --ϵͳ��
						0      ,         --�ɽ���
						'' ,             --�������ɽ���
						''      ,        --ϯλ��
						currency_code,   --����
						''    ,          --�ɽ�ʱ��
						sum(frzn_commi), 	--������
						oper_code,				--����Ա
						force_offset	--ǿƽ��־ 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							FROM   cust_basic
							WHERE  cust_class LIKE @mi_cust_class)
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

					select @rowcount_var = @@rowcount

					if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

					--order by done_no
					--select @test = '0,1,1,b'
					--����ϼƼ�¼
					if @mi_sum_flag <> '1'
					begin
						if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
				END
			END
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '0'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ��
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--��������� = '' or currency_code = ������֣�
				--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						SELECT	entrust_no   ,  --ί�к�
							cust_no      ,  --�ͻ���
							cust_name    ,  --�ͻ�����
							tx_no        ,  --���ױ���
							exch_code    ,  --����������
							vari_code    ,  --Ʒ�ִ���
							deliv_date   ,  --������
							done_qty	    ,  --�ɽ���
							done_price   ,  --�ɽ���
							eo_flag      ,  --��ƽ���
							sh_flag      ,  --Ͷ�����
							bs_flag      ,  --��������
							sys_no       ,  --ϵͳ��
							done_no      ,  --�ɽ���
							exch_done_no ,  --�������ɽ���
							seat_no      ,  --ϯλ��
							currency_code,  --����
							done_time    ,  --�ɽ�ʱ��
							frzn_commi   , 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						order by done_no

						select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						if @mi_sum_flag <> '1'
						begin
							if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
						if (@mi_cust_no = '')
						begin
							SELECT	entrust_no   ,  --ί�к�
								cust_no      ,  --�ͻ���
								cust_name    ,  --�ͻ�����
								tx_no        ,  --���ױ���
								exch_code    ,  --����������
								vari_code    ,  --Ʒ�ִ���
								deliv_date   ,  --������
								done_qty	    ,  --�ɽ���
								done_price   ,  --�ɽ���
								eo_flag      ,  --��ƽ���
								sh_flag      ,  --Ͷ�����
								bs_flag      ,  --��������
								sys_no       ,  --ϵͳ��
								done_no      ,  --�ɽ���
								exch_done_no ,  --�������ɽ���
								seat_no      ,  --ϯλ��
								currency_code,  --����
								done_time    ,  --�ɽ�ʱ��
								frzn_commi   , 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							order by done_no
						end
						else
						begin
							SELECT	entrust_no   ,  --ί�к�
								cust_no      ,  --�ͻ���
								cust_name    ,  --�ͻ�����
								tx_no        ,  --���ױ���
								exch_code    ,  --����������
								vari_code    ,  --Ʒ�ִ���
								deliv_date   ,  --������
								done_qty	    ,  --�ɽ���
								done_price   ,  --�ɽ���
								eo_flag      ,  --��ƽ���
								sh_flag      ,  --Ͷ�����
								bs_flag      ,  --��������
								sys_no       ,  --ϵͳ��
								done_no      ,  --�ɽ���
								exch_done_no ,  --�������ɽ���
								seat_no      ,  --ϯλ��
								currency_code,  --����
								done_time    ,  --�ɽ�ʱ��
								frzn_commi   , 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							order by done_no
		        			end


						select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

						--select @test = '0,1,0,a'
						--����ϼƼ�¼
						--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
						if @mi_sum_flag <> '1'
						begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end

			          		end
			          	end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ��
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--select @test = '0,1,0,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
				END
			END
			ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and ������Ա = �������Ա����
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
				--insert into #tmp
				--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						SELECT	0   ,		--ί�к�
							cust_no      ,   --�ͻ���
							cust_name    ,          --�ͻ�����
							tx_no        ,   --���ױ���
							exch_code    ,   --����������
							vari_code    ,   --Ʒ�ִ���
							deliv_date   ,   --������
							sum(done_qty),   --�ɽ���
							done_price   ,   --�ɽ���
							eo_flag      ,   --��ƽ���
							sh_flag      ,   --Ͷ�����
							bs_flag      ,   --��������
							''       ,       --ϵͳ��
							0      ,         --�ɽ���
							'' ,             --�������ɽ���
							''      ,        --ϯλ��
							currency_code,   --����
							''    ,          --�ɽ�ʱ��
							sum(frzn_commi), 	--������
							oper_code,				--����Ա
							force_offset	--ǿƽ��־ 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	oper_code = @mi_oper_code
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
						if (@mi_cust_no = '')
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

						end
						else
						begin
							SELECT	0   ,		--ί�к�
								cust_no      ,   --�ͻ���
								cust_name    ,          --�ͻ�����
								tx_no        ,   --���ױ���
								exch_code    ,   --����������
								vari_code    ,   --Ʒ�ִ���
								deliv_date   ,   --������
								sum(done_qty),   --�ɽ���
								done_price   ,   --�ɽ���
								eo_flag      ,   --��ƽ���
								sh_flag      ,   --Ͷ�����
								bs_flag      ,   --��������
								''       ,       --ϵͳ��
								0      ,         --�ɽ���
								'' ,             --�������ɽ���
								''      ,        --ϯλ��
								currency_code,   --����
								''    ,          --�ɽ�ʱ��
								sum(frzn_commi), 	--������
								oper_code,				--����Ա
								force_offset	--ǿƽ��־ 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			--order by done_no
		          			--select @test = '0,0,1,a'
		          			--����ϼƼ�¼
		          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
									select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end
			          	end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
				--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
				--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--and ������Ա = �������Ա����
				--��������� = '' or currency_code = ������֣�
				--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
	          			--insert into #tmp
	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	oper_code = @mi_oper_code
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '0,0,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
			END
			ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '0'
			BEGIN
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and ������ͻ��� = '' or �ͻ��� = ����ͻ��ţ�
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and ������Ա = �������Ա��
	          		--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          		--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
	          			if @if_batch = '1'
					begin
		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
		          		  	end
					end
					else
					begin
		          			if (@mi_cust_no = '')
		          			begin
			          			SELECT entrust_no   ,  --ί�к�
			          			       cust_no      ,  --�ͻ���
			          			       cust_name    ,  --�ͻ�����
			          			       tx_no        ,  --���ױ���
			          			       exch_code    ,  --����������
			          			       vari_code    ,  --Ʒ�ִ���
			          			       deliv_date   ,  --������
			          			       done_qty	    ,  --�ɽ���
			          			       done_price   ,  --�ɽ���
			          			       eo_flag      ,  --��ƽ���
			          			       sh_flag      ,  --Ͷ�����
			          			       bs_flag      ,  --��������
			          			       sys_no       ,  --ϵͳ��
			          			       done_no      ,  --�ɽ���
			          			       exch_done_no ,  --�������ɽ���
			          			       seat_no      ,  --ϯλ��
			          			       currency_code,  --����
			          			       done_time    ,  --�ɽ�ʱ��
			          			       frzn_commi   , 	--������
			          			       oper_code,				--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			order by done_no
		          			end
		          			else
		          			begin
			          			SELECT entrust_no   ,  --ί�к�
			          			       cust_no      ,  --�ͻ���
			          			       cust_name    ,  --�ͻ�����
			          			       tx_no        ,  --���ױ���
			          			       exch_code    ,  --����������
			          			       vari_code    ,  --Ʒ�ִ���
			          			       deliv_date   ,  --������
			          			       done_qty	    ,  --�ɽ���
			          			       done_price   ,  --�ɽ���
			          			       eo_flag      ,  --��ƽ���
			          			       sh_flag      ,  --Ͷ�����
			          			       bs_flag      ,  --��������
			          			       sys_no       ,  --ϵͳ��
			          			       done_no      ,  --�ɽ���
			          			       exch_done_no ,  --�������ɽ���
			          			       seat_no      ,  --ϯλ��
			          			       currency_code,  --����
			          			       done_time    ,  --�ɽ�ʱ��
			          			       frzn_commi   , 	--������
			          			       oper_code,				--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			order by done_no
		          			end
		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			--select @test = '0,0,0,a'
		          			--����ϼƼ�¼
		          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          		  	end
					end
				END
				ELSE
				BEGIN
				--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
				--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
				--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
				--and���ͻ��� In ���ͻ�������Ϣ�����в鵽����������ͻ����еĿͻ��ţ�
				--and ������Ա = �������Ա��
				--��������� = '' or currency_code = ������֣�
					--insert into #tmp
					SELECT entrust_no   ,  --ί�к�
					       cust_no      ,  --�ͻ���
					       cust_name    ,  --�ͻ�����
					       tx_no        ,  --���ױ���
					       exch_code    ,  --����������
					       vari_code    ,  --Ʒ�ִ���
					       deliv_date   ,  --������
					       done_qty	    ,  --�ɽ���
					       done_price   ,  --�ɽ���
					       eo_flag      ,  --��ƽ���
					       sh_flag      ,  --Ͷ�����
					       bs_flag      ,  --��������
					       sys_no       ,  --ϵͳ��
					       done_no      ,  --�ɽ���
					       exch_done_no ,  --�������ɽ���
					       seat_no      ,  --ϯλ��
					       currency_code,  --����
					       done_time    ,  --�ɽ�ʱ��
					       frzn_commi   , 	--������
					       oper_code,				--����Ա
					       force_offset	--ǿƽ��־ 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							    FROM   cust_basic
							    WHERE  cust_class LIKE @mi_cust_class)
					AND	oper_code = @mi_oper_code
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					order by done_no

					select @rowcount_var = @@rowcount

					if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

		  			--select @test = '0,0,0,b'
		  			--����ϼƼ�¼
		  			if @mi_sum_flag <> '1'
		  			begin
		  				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
		          	END
			end
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '2'
			begin
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          			--insert into #tmp
					--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
					if @if_batch = '1'
					begin
						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
						if (@mi_cust_no = '')
						begin
							SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

						end
						else
						begin
							SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

						end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			--order by done_no
		          			--select @t_vari_code, @t_deliv_date
		          			--select @test = '0,1,1,a'
		          			--����ϼƼ�¼
		          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end
			          	end
				END
				ELSE
				BEGIN
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '0,1,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
	          	end
	          	else IF @mi_done_flag = '0' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          			--insert into #tmp
	          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
	          			if @if_batch = '1'
					begin
		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          			if (@mi_cust_no = '')
		          			begin
			          			SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
						end
						else
						begin
			          			SELECT entrust_no   ,	--ί�к�
			          			       cust_no      ,   --�ͻ���
			          			       cust_name    ,   --�ͻ�����
			          			       tx_no        ,   --���ױ���
			          			       exch_code    ,   --����������
			          			       vari_code    ,   --Ʒ�ִ���
			          			       deliv_date   ,   --������
			          			       sum(done_qty),   --�ɽ���
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
			          			       eo_flag      ,   --��ƽ���
			          			       sh_flag      ,   --Ͷ�����
			          			       bs_flag      ,   --��������
			          			       sys_no       ,   --ϵͳ��
			          			       0      ,         --�ɽ���
			          			       '' ,             --�������ɽ���
			          			       seat_no      ,   --ϯλ��
			          			       currency_code,   --����
			          			       ''    ,          --�ɽ�ʱ��
			          			       sum(frzn_commi), --������
			          			       oper_code,	--����Ա
			          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1
			        		end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
					          	else
					          	begin
					          		if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '1'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          	end
			          		end

		          			--order by done_no
		          			--select @test = '0,0,1,a'
		          			--����ϼƼ�¼
		          			--6.3.0.1 20061103 ��cust_real_done��ѯ�����е�cust_no��or���Ӳ�ֳ�if else�ṹ
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
		          				else
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
		          				end
			          		end
			          	end
				END
				ELSE
				BEGIN
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	oper_code = @mi_oper_code
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '0,0,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   cust_basic
			          					    WHERE  cust_class LIKE @mi_cust_class)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
	          	end
		END
		ELSE IF @t_if_access = '1'	--������
		BEGIN
		--6.
			--select @test = '6'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN

	          			if @if_batch = '1'
					begin
						SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
						--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
						EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
						IF @ocode <> 0
						BEGIN
							GOTO l_fatal
						END
						--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
						--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
						--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
						--and ���ͻ��� = ����ͻ��ţ�
						--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)��
						--��������� = '' or currency_code = ������֣�
						--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
						--insert into #tmp
		          			SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--order by done_no
		          			--select @test = '1,1,1,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ����
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			--insert into #tmp
	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '1,1,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
			END
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '0'
			BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
		          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--��������� = '' or currency_code = ������֣�
		          			--insert into #tmp
		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--select @test = '1,1,0,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--select @test = '1,1,0,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class like @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
	          	END
	          	ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '1'
	          	BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
		          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
		          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա����
		          		--��������� = '' or currency_code = ������֣�
		          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
		          			--insert into #tmp
		          			SELECT 0   ,		--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,          --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       done_price   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       ''       ,       --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       ''      ,        --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--order by done_no
		          			--select @test = '1,0,1,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա����
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			--insert into #tmp
	          			SELECT 0   ,		--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,          --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       done_price   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       ''       ,       --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       ''      ,        --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '1,0,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
	          	END
	          	ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '0'
	          	BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
		          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա��
		          		--��������� = '' or currency_code = ������֣�
		          			--insert into #tmp
		          			SELECT entrust_no   ,  --ί�к�
		          			       cust_no      ,  --�ͻ���
		          			       cust_name    ,  --�ͻ�����
		          			       tx_no        ,  --���ױ���
		          			       exch_code    ,  --����������
		          			       vari_code    ,  --Ʒ�ִ���
		          			       deliv_date   ,  --������
		          			       done_qty	    ,  --�ɽ���
		          			       done_price   ,  --�ɽ���
		          			       eo_flag      ,  --��ƽ���
		          			       sh_flag      ,  --Ͷ�����
		          			       bs_flag      ,  --��������
		          			       sys_no       ,  --ϵͳ��
		          			       done_no      ,  --�ɽ���
		          			       exch_done_no ,  --�������ɽ���
		          			       seat_no      ,  --ϯλ��
		          			       currency_code,  --����
		          			       done_time    ,  --�ɽ�ʱ��
		          			       frzn_commi   , 	--������
		          			       oper_code,				--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			order by done_no

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--select @test = '1,0,0,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ����ѯ������
	          		--���������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա��
	          		--��������� = '' or currency_code = ������֣�
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --ί�к�
	          			       cust_no      ,  --�ͻ���
	          			       cust_name    ,  --�ͻ�����
	          			       tx_no        ,  --���ױ���
	          			       exch_code    ,  --����������
	          			       vari_code    ,  --Ʒ�ִ���
	          			       deliv_date   ,  --������
	          			       done_qty	    ,  --�ɽ���
	          			       done_price   ,  --�ɽ���
	          			       eo_flag      ,  --��ƽ���
	          			       sh_flag      ,  --Ͷ�����
	          			       bs_flag      ,  --��������
	          			       sys_no       ,  --ϵͳ��
	          			       done_no      ,  --�ɽ���
	          			       exch_done_no ,  --�������ɽ���
	          			       seat_no      ,  --ϯλ��
	          			       currency_code,  --����
	          			       done_time    ,  --�ɽ�ʱ��
	          			       frzn_commi   , 	--������
	          			       oper_code,				--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and    oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			order by done_no

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--select @test = '1,0,0,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and    oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          							AND	oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and    oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
	          			end
	          		END
	          	end
	          	else IF @mi_done_flag = '1' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          			--insert into #tmp
		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--order by done_no
		          			--select @test = '1,1,1,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			--and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--��������� = '' or currency_code = ������֣�
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ����
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '1,1,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end
	          		END
	          	end
	          	else IF @mi_done_flag = '0' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> ''
	          		BEGIN
	          			if @if_batch = '1'
					begin
						SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no IN (	SELECT	a.cust_no
									FROM	oper_all_cust a,#tmp_cust b
									WHERE	a.cust_no = b.cust_no
									and	a.oper_code = @mi_oper_code)
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no IN (	SELECT	a.cust_no
											FROM	oper_all_cust a,#tmp_cust b
											WHERE	a.cust_no = b.cust_no
											and	a.oper_code = @mi_oper_code)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
					end
					else
					begin
		          		--�жϱ�����Ա�Ƿ��д��ÿͻ���Ȩ�ޣ����û�У������˳�
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			end
		          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
		          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
		          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
		          		--and ���ͻ��� = ����ͻ��ţ�
		          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
		          		--and ������Ա = �������Ա����
		          		--��������� = '' or currency_code = ������֣�
		          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ�����
		          			--insert into #tmp
		          			SELECT entrust_no   ,	--ί�к�
		          			       cust_no      ,   --�ͻ���
		          			       cust_name    ,   --�ͻ�����
		          			       tx_no        ,   --���ױ���
		          			       exch_code    ,   --����������
		          			       vari_code    ,   --Ʒ�ִ���
		          			       deliv_date   ,   --������
		          			       sum(done_qty),   --�ɽ���
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
		          			       eo_flag      ,   --��ƽ���
		          			       sh_flag      ,   --Ͷ�����
		          			       bs_flag      ,   --��������
		          			       sys_no       ,   --ϵͳ��
		          			       0      ,         --�ɽ���
		          			       '' ,             --�������ɽ���
		          			       seat_no      ,   --ϯλ��
		          			       currency_code,   --����
		          			       ''    ,          --�ɽ�ʱ��
		          			       sum(frzn_commi), --������
		          			       oper_code,	--����Ա
		          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

		          			--order by done_no
		          			--select @test = '1,0,1,a'
		          			--����ϼƼ�¼
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
				          		else
				          		begin
				          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
				          			FROM   cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and    oper_code = @mi_oper_code
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--��ѯ���ͻ�ʵʱ�ɽ�������������Ϣ������еķ�group by�а������ֶ�
	          		--����ͨ�������ܹ�Ψһȷ�����ֶ��ⶼ��Ϊ�ջ���0�����еĳɽ�����Ϊsum(�ɽ�����) as �ɽ�������
	          		--��ѯ�����ǣ��������Լ�� = ''��or ��Ʒ�ִ��� = ��ֵ�Ʒ�ִ��� and ������ = ��ֵĽ����ڣ���
	          		--and (����ϯλ�� = '' or ϯλ�� = ����ϯλ��)
	          		--and���ͻ��� in ��������Ա�������пͻ������в鵽�ĸò���Ա�ɴ��Ŀͻ��ţ���ѯ��������ͻ��� = '' or �ͻ��� = ����ͻ��ࣩ��
	          		--and ������Ա = �������Ա����
	          		--��������� = '' or currency_code = ������֣�
	          		--group by �ͻ��ţ����ױ��룬Ʒ�ִ��룬�����ڣ��ɽ��۸�������ǣ�Ͷ����ǣ���ƽ��ǣ����֡�
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--ί�к�
	          			       cust_no      ,   --�ͻ���
	          			       cust_name    ,   --�ͻ�����
	          			       tx_no        ,   --���ױ���
	          			       exch_code    ,   --����������
	          			       vari_code    ,   --Ʒ�ִ���
	          			       deliv_date   ,   --������
	          			       sum(done_qty),   --�ɽ���
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --�ɽ���
	          			       eo_flag      ,   --��ƽ���
	          			       sh_flag      ,   --Ͷ�����
	          			       bs_flag      ,   --��������
	          			       sys_no       ,   --ϵͳ��
	          			       0      ,         --�ɽ���
	          			       '' ,             --�������ɽ���
	          			       seat_no      ,   --ϯλ��
	          			       currency_code,   --����
	          			       ''    ,          --�ɽ�ʱ��
	          			       sum(frzn_commi), --������
	          			       oper_code,	--����Ա
	          			       force_offset	--ǿƽ��־ 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   oper_all_cust
	          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
	          					    and    oper_code = @mi_oper_code)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			and oper_code = @mi_oper_code
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--ǿƽ��־ 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '0'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

			          			select	'', '(��С��)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
			          			FROM	cust_real_done
			          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and	oper_code = @mi_oper_code
			          			AND	bs_flag = '1'
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
		          		end

	          			--order by done_no
	          			--select @test = '1,0,1,b'
	          			--����ϼƼ�¼
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
			          		else
			          		begin
			          			select '', '(�ϼ�)'+convert(varchar,count(*))+'��','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--ǿƽ��־ 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	cust_no IN (SELECT cust_no
			          					    FROM   oper_all_cust
			          					    WHERE  (@mi_cust_class = '' OR cust_class LIKE @mi_cust_class)
			          					    and    oper_code = @mi_oper_code)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			and oper_code = @mi_oper_code
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          		end
					end	--for if @mi_sum_flag <> '1'
				end	--for else
			end	--for IF @mi_done_flag = '0' AND @mi_bind_flag = '2
		end	--for IF @t_if_access = '1'
		else
		begin
			select @ocode = -2, @omsg = '����Ա�Ų����ڻ����Ա����������Ч'
			goto l_fatal
		end

	          select @ocode = @@error
	          if @ocode <> 0
	          begin
	          	select @ocode = -3, @omsg = '��ѯ�ͻ����ճɽ���ʧ��'
	          	goto l_fatal
	          end
	end

	  --���������ͺϼƼ�¼
	  --select * from #tmp
	  --select '', '�ϼ�', '', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi) from #tmp

          return 0
l_fatal:
          select "fatal"=@ocode, @omsg
          return -1
end
go
declare @update_flag char
exec	sp_upgrade_control
	'6.8.2.1',			--�汾��
	'2',				--������־
	'p854042',			--sp���ܺ�
	@update_flag output		--�޸ı�־
if @update_flag <> '0'
	print '���ִ��󡣴����洢����: 854042 , ��ѯ���ճɽ�,ʧ�ܣ�'
else
	print '�����洢����: 854042 , ��ѯ���ճɽ�'
go
