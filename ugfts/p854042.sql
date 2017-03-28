/*#$&B#----脚本转换器 For SyBase	03-12-04*/
/* --------------------------------------------------------------
 * 程序名称：p854042.sql
 * 版本信息：6.8.2.x
 * 程序功能：查询当日成交
 * ==============================================================

输入参数：
          操作员       scust_no  oper_code varchar(10)
          席位号       sserial2  seat_no   varchar(10)
          客户号       sholder_ac_no cust_no varchar(16)
          客户类       sserial1  cust_class char(10)
          合约号       scust_auth contract_code varchar(16)
          合并标志      sstatus1  bind_flag
          所有成交单标记   smain_flag done_flag
          币种        scurrency_type currency_code
          是否输出合计           sum_flag char

输出参数：
          委托号       lserial0
          客户号       sholder_ac_no
          客户名称      sname
          交易编码      sholder_ac_no2
          交易所代码     smarket_code
          品种代码      sstock_code
          交割期       sdate1
          成交量       lvol1
          成交价       damt2
          开平标记      sstatus3
          投保标记      sstatus4
          买卖方向      sstatus2
          系统号       sorder0
          成交号       lvol11
          交易所成交号    sserial0
          席位号       sserial2
          币种        scurrency_type
          成交时间      stime3
          手续费
          操作员      scust_no
处理逻辑：

注意点：


 * ==============================================================
 * 创建日期:    20031106
 * 生成器版本:  1.0
 * 编码者:      hezhenhua
 * --------------------------------------------------------------
 * 修改日期：   20040205
 * 修改人员：   hezhenhua
 * 修改描述：   增加排序和合计记录输出
 * 备注信息     6.0.0.1
 * --------------------------------------------------------------
 * 修改日期：   20040325
 * 修改人员：   hezhenhua
 * 修改描述：   合计记录中增加成交均价
 * 备注信息     6.0.0.2
 * --------------------------------------------------------------
 * 修改日期：   20040610
 * 修改人员：   hezhenhua
 * 修改描述：   更改查询条件，把品种代码的"like"，改为"="
 * 备注信息     6.0.0.3
 * --------------------------------------------------------------
 * 修改日期：   20040728
 * 修改人员：   hezhenhua
 * 修改描述：   合并成交单时，增加输出“客户名称”字段
 * 备注信息     6.0.0.4
 * --------------------------------------------------------------
 * 修改日期：   20040809
 * 修改人员：   hezhenhua
 * 修改描述：   对有限制德操作员的查询增加条件"oper_code = @mi_oper_code"
 * 备注信息     6.0.0.5
 * --------------------------------------------------------------
 * 修改日期：   20040825
 * 修改人员：   hezhenhua
 * 修改描述：   增加输出参数“操作员”
 * 备注信息     6.0.0.6
 * --------------------------------------------------------------
 * 修改日期：   20041008
 * 修改人员：   hezhenhua
 * 修改描述：   根据表索引顺序调整条件
 * 备注信息     6.0.0.7
 * --------------------------------------------------------------
 * 修改日期：   20041105
 * 修改人员：   wtbao
 * 修改描述：   把所有正在使用的order by子句中的条件entrust_no,done_no
 		改为目前的done_no。目的，提供交易监控服务器使用，同时，
 		done_no还是该表的聚集索引。
 * 备注信息     6.0.0.8
 * --------------------------------------------------------------
 * 修改日期：   20041123
 * 修改人员：   hezhenhua
 * 修改描述：   增加输入字段“sum_flag”，控制是否输出合计信息（1：不输出，其它：输出）
 * 备注信息     6.0.0.9
 * --------------------------------------------------------------
 * 修改日期：   20050322
 * 修改人员：   wtbao
 * 修改描述：	在合并标志输入项中增加一项可能的输入值“2”，作为合并同笔委托的标志。
 		目前该字段可能输入项为3个“0”，“1”，“2”，含义分别为对成交记录不做任何
 		处理、合并同客户同品种同价位合并成交单、合并同一委托的分笔成交单
 * 备注信息     6.0.2.1
 * --------------------------------------------------------------
 * 修改日期：   20050322
 * 修改人员：   wtbao
 * 修改描述：	修改原合计信息中第20个字段输出成交均价、第21个字段输出''的bug。
 		问题原因应该是原来输出中包含成交均价，但是后来把成交均价拿掉了，
 		在输出的字段中已经去掉了，但是忘记在合计的输出中作相应的修改。
 		由于应用服务器把预期varchar型而实际输出数值型的输出置为空，而合计的操作员
 		也是恰好也是空，所以问题一直没有被发现。
 * 备注信息     6.0.2.2
 * --------------------------------------------------------------
 * 修改日期：   20061103
 * 修改人员：   王智颖
 * 修改描述：   性能优化,把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
 * 备注信息     6.3.0.1
 * --------------------------------------------------------------
 * 修改日期：	20061123
 * 修改人员：	jk
 * 修改描述：	增加强平标志
 * 备注信息：	6.4.0.1
 * --------------------------------------------------------------
 * 修改日期：	20081008
 * 修改人员：	jk
 * 修改描述：	增加排序方式的处理和批号查询的处理
 * 备注信息:	6.6.5.1
 * --------------------------------------------------------------
 * 修改日期：	20100119
 * 修改人员：	jk
 * 修改描述：	将网上交易查询分支单独出来
 * 备注信息:	6.8.0.1
 * --------------------------------------------------------------
 * 修改日期：	20100421
 * 修改人员：	zlm
 * 修改描述：	增加查询条件“开平”（下拉框，下拉框内容为空、0-开、1-平，默认为空），
 		空代表全部，0-开代表开仓单，1-平代表平仓单，包括平今和平仓。
 * 备注信息:	6.8.2.1
 * --------------------------------------------------------------

测试脚本
EXEC p854042
           '',    --操作员    varchar(10)
           '',    --席位号    varchar(12)
           '',    --客户号    varchar(15)
           '',    --客户类    varchar(12)
           '',    --合约号    varchar(20)
           '',    --合并标志    char
           '',    --所有成交单标记    char
           '',     --币种    char(2)
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
	'6.8.2.1',			--版本号
	'1',				--操作标志
	'p854042',			--sp功能号
	''				--修改标志
go

create  procedure p854042
	@mi_oper_code    varchar(10),    --操作员
	@mi_seat_no    varchar(12),    --席位号
	@mi_cust_no    varchar(15),    --客户号
	@mi_cust_class    varchar(12),    --客户类
	@mi_contract_code    varchar(20),    --合约号
	@mi_bind_flag    char,    --合并标志
	@mi_done_flag    char,    --所有成交单标记
	@mi_currency_code    char(2),     --币种
	@mi_sum_flag	char,	--是否输出合计
	@mi_order_by	char(1) = '1',	--排序方式	20081008 6.6.5.1
	@mi_subtotal	char(1) = '0',	--是否需要小计	20081008 6.6.5.1
	@mi_eo_flag     char(1) = ''  	--开平 20100421 6.8.2.1  数据字典 80
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

          --创建输出临时表
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
          	select @ocode = -1, @omsg = '创建临时表失败'
          	goto l_fatal
          end

	create	table #tmp_cust (
		cust_no varchar(16)
		)

	select	@t_vari_name = '',
		@t_deliv_date = ''

	--20100119 将网上交易查询分支单独出来
	if @mi_seat_no = '' and @mi_cust_no <> '' and @mi_cust_class = '' and @mi_contract_code = ''
		and @mi_bind_flag = '0' and @mi_done_flag = '1' and @mi_currency_code = '1' and @mi_sum_flag = ''
		and @mi_order_by = '' and @mi_subtotal = ''
	begin
		SELECT	entrust_no   ,  --委托号
			cust_no      ,  --客户号
			cust_name    ,  --客户名称
			tx_no        ,  --交易编码
			exch_code    ,  --交易所代码
			vari_code    ,  --品种代码
			deliv_date   ,  --交割期
			done_qty	    ,  --成交量
			done_price   ,  --成交价
			eo_flag      ,  --开平标记
			sh_flag      ,  --投保标记
			bs_flag      ,  --买卖方向
			sys_no       ,  --系统号
			done_no      ,  --成交号
			exch_done_no ,  --交易所成交号
			seat_no      ,  --席位号
			currency_code,  --币种
			done_time    ,  --成交时间
			frzn_commi   , 	--手续费
			oper_code,				--操作员
			force_offset	--强平标志 20061123 6.4.0.1
		FROM   cust_real_done
		WHERE  (cust_no = @mi_cust_no)
		AND	(currency_code = @mi_currency_code)
		order by done_no

/*		--20100119 网上交易不要合计
		select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
		FROM   cust_real_done
		WHERE  (cust_no = @mi_cust_no)
		AND	(currency_code = @mi_currency_code)
*/
		return 0
	end

          --wtbao 20050322 下面的代码根据输入的@mi_bind_flag进行分支处理，如果输入的为“0”和“1”，
          --则按照原有的模式处理；如果输入的是“2”，则按照新增分支处理；如果输入其他，则报错；
          if (@mi_bind_flag not in ('0','1','2'))
          begin
          	select @ocode = -1, @omsg = '输入的查询参数合并标记不正确'
          	goto l_fatal
          end

	--20081008 6.6.5.1 判断是否组号查询
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
		  	select @omsg='查询批量委托设置表出错'
		      	goto l_fatal
		end

		if @rowcount_var = 0
		begin
		  	select @omsg='该批量组号不存在'
		      	goto l_fatal
		end
	end
	else
	begin
		select	@if_batch = '0'
	end

          -- declare @test char(8)
          -- select @test = '1'
          --1．	判断输入的合约号是否为空，如果为空，跳至4，否则， 执行2
          IF @mi_contract_code <> ''
          BEGIN
          	--select @test = '2'
          	--2．	拆分合约号为品种代码+交割期

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
          --4．在《操作员》表中查找输入操作员是否限制标记，如果没有限制，执行5，否则，执行6
          declare @t_if_access char(1)

          select @t_if_access = a.if_access
          	 from operator as a
          	 where a.oper_code = @mi_oper_code

	--20081008 6.6.5.1 将查询逻辑分成正序和倒序2段，同时加入组号查询。代码从2000翻为5000，呜咕~~
	if @mi_order_by = '0'
	begin
		IF @t_if_access = '0'	--没有限制
		BEGIN
			--5.
			--select @test = '5'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
					--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select	'', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          		SELECT	0   ,		--委托号
							cust_no      ,   --客户号
							cust_name    ,          --客户名称
							tx_no        ,   --交易编码
							exch_code    ,   --交易所代码
							vari_code    ,   --品种代码
							deliv_date   ,   --交割期
							sum(done_qty),   --成交量
							done_price   ,   --成交价
							eo_flag      ,   --开平标记
							sh_flag      ,   --投保标记
							bs_flag      ,   --买卖方向
							''       ,       --系统号
							0      ,         --成交号
							'' ,             --交易所成交号
							''      ,        --席位号
							currency_code,   --币种
							''    ,          --成交时间
							sum(frzn_commi), 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
						FROM	cust_real_done
						WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
							if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
							SELECT 0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
			          	end
				END
				ELSE
				BEGIN
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
					if @mi_sum_flag <> '1'
					begin
						if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

					SELECT	0   ,		--委托号
						cust_no      ,   --客户号
						cust_name    ,          --客户名称
						tx_no        ,   --交易编码
						exch_code    ,   --交易所代码
						vari_code    ,   --品种代码
						deliv_date   ,   --交割期
						sum(done_qty),   --成交量
						done_price   ,   --成交价
						eo_flag      ,   --开平标记
						sh_flag      ,   --投保标记
						bs_flag      ,   --买卖方向
						''       ,       --系统号
						0      ,         --成交号
						'' ,             --交易所成交号
						''      ,        --席位号
						currency_code,   --币种
						''    ,          --成交时间
						sum(frzn_commi), 	--手续费
						oper_code,				--操作员
						force_offset	--强平标志 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							FROM   cust_basic
							WHERE  cust_class LIKE @mi_cust_class)
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
				END
			END
			ELSE IF @mi_done_flag = '1' AND @mi_bind_flag = '0'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--查询《客户实时成交表》，获得输出信息，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--（输入币种 = '' or currency_code = 输入币种）
				--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
						begin
							if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '1'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
				          		end
			          		end

						SELECT	entrust_no   ,  --委托号
							cust_no      ,  --客户号
							cust_name    ,  --客户名称
							tx_no        ,  --交易编码
							exch_code    ,  --交易所代码
							vari_code    ,  --品种代码
							deliv_date   ,  --交割期
							done_qty	    ,  --成交量
							done_price   ,  --成交价
							eo_flag      ,  --开平标记
							sh_flag      ,  --投保标记
							bs_flag      ,  --买卖方向
							sys_no       ,  --系统号
							done_no      ,  --成交号
							exch_done_no ,  --交易所成交号
							seat_no      ,  --席位号
							currency_code,  --币种
							done_time    ,  --成交时间
							frzn_commi   , 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
							SELECT	entrust_no   ,  --委托号
								cust_no      ,  --客户号
								cust_name    ,  --客户名称
								tx_no        ,  --交易编码
								exch_code    ,  --交易所代码
								vari_code    ,  --品种代码
								deliv_date   ,  --交割期
								done_qty	    ,  --成交量
								done_price   ,  --成交价
								eo_flag      ,  --开平标记
								sh_flag      ,  --投保标记
								bs_flag      ,  --买卖方向
								sys_no       ,  --系统号
								done_no      ,  --成交号
								exch_done_no ,  --交易所成交号
								seat_no      ,  --席位号
								currency_code,  --币种
								done_time    ,  --成交时间
								frzn_commi   , 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
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
							SELECT	entrust_no   ,  --委托号
								cust_no      ,  --客户号
								cust_name    ,  --客户名称
								tx_no        ,  --交易编码
								exch_code    ,  --交易所代码
								vari_code    ,  --品种代码
								deliv_date   ,  --交割期
								done_qty	    ,  --成交量
								done_price   ,  --成交价
								eo_flag      ,  --开平标记
								sh_flag      ,  --投保标记
								bs_flag      ,  --买卖方向
								sys_no       ,  --系统号
								done_no      ,  --成交号
								exch_done_no ,  --交易所成交号
								seat_no      ,  --席位号
								currency_code,  --币种
								done_time    ,  --成交时间
								frzn_commi   , 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and （操作员 = 输入操作员），
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
				--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT	0   ,		--委托号
							cust_no      ,   --客户号
							cust_name    ,          --客户名称
							tx_no        ,   --交易编码
							exch_code    ,   --交易所代码
							vari_code    ,   --品种代码
							deliv_date   ,   --交割期
							sum(done_qty),   --成交量
							done_price   ,   --成交价
							eo_flag      ,   --开平标记
							sh_flag      ,   --投保标记
							bs_flag      ,   --买卖方向
							''       ,       --系统号
							0      ,         --成交号
							'' ,             --交易所成交号
							''      ,        --席位号
							currency_code,   --币种
							''    ,          --成交时间
							sum(frzn_commi), 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	oper_code = @mi_oper_code
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
									select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
		          			end
			          	end
				END
				ELSE
				BEGIN
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--and （操作员 = 输入操作员），
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
				END
			END
			ELSE IF @mi_done_flag = '0' AND @mi_bind_flag = '0'
			BEGIN
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          		--查询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and （输入客户号 = '' or 客户号 = 输入客户号）
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and （操作员 = 输入操作员）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          		--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          			SELECT entrust_no   ,  --委托号
			          			       cust_no      ,  --客户号
			          			       cust_name    ,  --客户名称
			          			       tx_no        ,  --交易编码
			          			       exch_code    ,  --交易所代码
			          			       vari_code    ,  --品种代码
			          			       deliv_date   ,  --交割期
			          			       done_qty	    ,  --成交量
			          			       done_price   ,  --成交价
			          			       eo_flag      ,  --开平标记
			          			       sh_flag      ,  --投保标记
			          			       bs_flag      ,  --买卖方向
			          			       sys_no       ,  --系统号
			          			       done_no      ,  --成交号
			          			       exch_done_no ,  --交易所成交号
			          			       seat_no      ,  --席位号
			          			       currency_code,  --币种
			          			       done_time    ,  --成交时间
			          			       frzn_commi   , 	--手续费
			          			       oper_code,				--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          			SELECT entrust_no   ,  --委托号
			          			       cust_no      ,  --客户号
			          			       cust_name    ,  --客户名称
			          			       tx_no        ,  --交易编码
			          			       exch_code    ,  --交易所代码
			          			       vari_code    ,  --品种代码
			          			       deliv_date   ,  --交割期
			          			       done_qty	    ,  --成交量
			          			       done_price   ,  --成交价
			          			       eo_flag      ,  --开平标记
			          			       sh_flag      ,  --投保标记
			          			       bs_flag      ,  --买卖方向
			          			       sys_no       ,  --系统号
			          			       done_no      ,  --成交号
			          			       exch_done_no ,  --交易所成交号
			          			       seat_no      ,  --席位号
			          			       currency_code,  --币种
			          			       done_time    ,  --成交时间
			          			       frzn_commi   , 	--手续费
			          			       oper_code,				--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，查询条件是
				--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--and （操作员 = 输入操作员）
				--（输入币种 = '' or currency_code = 输入币种）
					--insert into #tmp
					if @mi_sum_flag <> '1'
		  			begin
		  				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

					SELECT entrust_no   ,  --委托号
					       cust_no      ,  --客户号
					       cust_name    ,  --客户名称
					       tx_no        ,  --交易编码
					       exch_code    ,  --交易所代码
					       vari_code    ,  --品种代码
					       deliv_date   ,  --交割期
					       done_qty	    ,  --成交量
					       done_price   ,  --成交价
					       eo_flag      ,  --开平标记
					       sh_flag      ,  --投保标记
					       bs_flag      ,  --买卖方向
					       sys_no       ,  --系统号
					       done_no      ,  --成交号
					       exch_done_no ,  --交易所成交号
					       seat_no      ,  --席位号
					       currency_code,  --币种
					       done_time    ,  --成交时间
					       frzn_commi   , 	--手续费
					       oper_code,				--操作员
					       force_offset	--强平标志 20061123 6.4.0.1
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
					--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
							SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
							SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
			          	end
				END
				ELSE
				BEGIN
					if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
	          		END
	          	end
	          	else IF @mi_done_flag = '0' AND @mi_bind_flag = '2'
	          	begin
	          		IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
	          		BEGIN
	          			--insert into #tmp
	          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
	          			if @if_batch = '1'
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
						if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				          				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          			SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
			          			SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				          		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			        		end
			          	end
				END
				ELSE
				BEGIN
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
	          		END
	          	end
		END
		ELSE IF @t_if_access = '1'	--有限制
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
						--判断本操作员是否有带该客户的权限，如果没有，报错，退出
						EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
						IF @ocode <> 0
						BEGIN
							GOTO l_fatal
						END
						--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
						--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
						--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
						--and （客户号 = 输入客户号）
						--and (输入席位号 = '' or 席位号 = 输入席位号)，
						--（输入币种 = '' or currency_code = 输入币种）
						--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
						if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				          			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				          	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类）），
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，查询条件是
		          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--（输入币种 = '' or currency_code = 输入币种）
		          			--insert into #tmp
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          		--询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
		          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
		          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员），
		          		--（输入币种 = '' or currency_code = 输入币种）
		          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员），
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，查询条件是
		          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员）
		          		--（输入币种 = '' or currency_code = 输入币种）
		          			--insert into #tmp
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END

		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			--and    oper_code = @mi_oper_code
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类）），
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
					end
					else
					begin
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			end
		          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
		          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
		          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员），
		          		--（输入币种 = '' or currency_code = 输入币种）
		          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			          	end
	          		END
	          		ELSE
	          		BEGIN
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员），
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
				end	--for else
			end	--for IF @mi_done_flag = '0' AND @mi_bind_flag = '2
		end	--for IF @t_if_access = '1'
		else
		begin
			select @ocode = -2, @omsg = '操作员号不存在或操作员访问限制无效'
			goto l_fatal
		end

	          select @ocode = @@error
	          if @ocode <> 0
	          begin
	          	select @ocode = -3, @omsg = '查询客户当日成交表失败'
	          	goto l_fatal
	          end
	end
	else	--if @mi_order_by = '1'
	begin
		IF @t_if_access = '0'	--没有限制
		BEGIN
			--5.
			--select @test = '5'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
				IF @mi_cust_no <> '' OR (@mi_cust_no = '' AND @mi_cust_class = '')
				BEGIN
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
					--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						SELECT	0   ,		--委托号
							cust_no      ,   --客户号
							cust_name    ,          --客户名称
							tx_no        ,   --交易编码
							exch_code    ,   --交易所代码
							vari_code    ,   --品种代码
							deliv_date   ,   --交割期
							sum(done_qty),   --成交量
							done_price   ,   --成交价
							eo_flag      ,   --开平标记
							sh_flag      ,   --投保标记
							bs_flag      ,   --买卖方向
							''       ,       --系统号
							0      ,         --成交号
							'' ,             --交易所成交号
							''      ,        --席位号
							currency_code,   --币种
							''    ,          --成交时间
							sum(frzn_commi), 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
						FROM	cust_real_done
						WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

						select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select	'', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select	'', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
							SELECT 0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM	cust_real_done
							WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

						end
						select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
		          			if @mi_sum_flag <> '1'
		          			begin
							if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
				--insert into #tmp
					SELECT	0   ,		--委托号
						cust_no      ,   --客户号
						cust_name    ,          --客户名称
						tx_no        ,   --交易编码
						exch_code    ,   --交易所代码
						vari_code    ,   --品种代码
						deliv_date   ,   --交割期
						sum(done_qty),   --成交量
						done_price   ,   --成交价
						eo_flag      ,   --开平标记
						sh_flag      ,   --投保标记
						bs_flag      ,   --买卖方向
						''       ,       --系统号
						0      ,         --成交号
						'' ,             --交易所成交号
						''      ,        --席位号
						currency_code,   --币种
						''    ,          --成交时间
						sum(frzn_commi), 	--手续费
						oper_code,				--操作员
						force_offset	--强平标志 20061123 6.4.0.1
					FROM   cust_real_done
					WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					AND	cust_no IN (SELECT cust_no
							FROM   cust_basic
							WHERE  cust_class LIKE @mi_cust_class)
					AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

					select @rowcount_var = @@rowcount

					if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
					--输出合计记录
					if @mi_sum_flag <> '1'
					begin
						if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--（输入币种 = '' or currency_code = 输入币种）
				--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						SELECT	entrust_no   ,  --委托号
							cust_no      ,  --客户号
							cust_name    ,  --客户名称
							tx_no        ,  --交易编码
							exch_code    ,  --交易所代码
							vari_code    ,  --品种代码
							deliv_date   ,  --交割期
							done_qty	    ,  --成交量
							done_price   ,  --成交价
							eo_flag      ,  --开平标记
							sh_flag      ,  --投保标记
							bs_flag      ,  --买卖方向
							sys_no       ,  --系统号
							done_no      ,  --成交号
							exch_done_no ,  --交易所成交号
							seat_no      ,  --席位号
							currency_code,  --币种
							done_time    ,  --成交时间
							frzn_commi   , 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
							SELECT	entrust_no   ,  --委托号
								cust_no      ,  --客户号
								cust_name    ,  --客户名称
								tx_no        ,  --交易编码
								exch_code    ,  --交易所代码
								vari_code    ,  --品种代码
								deliv_date   ,  --交割期
								done_qty	    ,  --成交量
								done_price   ,  --成交价
								eo_flag      ,  --开平标记
								sh_flag      ,  --投保标记
								bs_flag      ,  --买卖方向
								sys_no       ,  --系统号
								done_no      ,  --成交号
								exch_done_no ,  --交易所成交号
								seat_no      ,  --席位号
								currency_code,  --币种
								done_time    ,  --成交时间
								frzn_commi   , 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
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
							SELECT	entrust_no   ,  --委托号
								cust_no      ,  --客户号
								cust_name    ,  --客户名称
								tx_no        ,  --交易编码
								exch_code    ,  --交易所代码
								vari_code    ,  --品种代码
								deliv_date   ,  --交割期
								done_qty	    ,  --成交量
								done_price   ,  --成交价
								eo_flag      ,  --开平标记
								sh_flag      ,  --投保标记
								bs_flag      ,  --买卖方向
								sys_no       ,  --系统号
								done_no      ,  --成交号
								exch_done_no ,  --交易所成交号
								seat_no      ,  --席位号
								currency_code,  --币种
								done_time    ,  --成交时间
								frzn_commi   , 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
						--输出合计记录
						--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
						if @mi_sum_flag <> '1'
						begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          					end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and （输入客户号 = '' or 客户号 = 输入客户号）
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and （操作员 = 输入操作员），
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
				--insert into #tmp
				--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						SELECT	0   ,		--委托号
							cust_no      ,   --客户号
							cust_name    ,          --客户名称
							tx_no        ,   --交易编码
							exch_code    ,   --交易所代码
							vari_code    ,   --品种代码
							deliv_date   ,   --交割期
							sum(done_qty),   --成交量
							done_price   ,   --成交价
							eo_flag      ,   --开平标记
							sh_flag      ,   --投保标记
							bs_flag      ,   --买卖方向
							''       ,       --系统号
							0      ,         --成交号
							'' ,             --交易所成交号
							''      ,        --席位号
							currency_code,   --币种
							''    ,          --成交时间
							sum(frzn_commi), 	--手续费
							oper_code,				--操作员
							force_offset	--强平标志 20061123 6.4.0.1
						FROM   cust_real_done
						WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
						AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
						and	cust_no in (select cust_no from #tmp_cust)
						AND	oper_code = @mi_oper_code
						AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
						--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
						GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

						end
						else
						begin
							SELECT	0   ,		--委托号
								cust_no      ,   --客户号
								cust_name    ,          --客户名称
								tx_no        ,   --交易编码
								exch_code    ,   --交易所代码
								vari_code    ,   --品种代码
								deliv_date   ,   --交割期
								sum(done_qty),   --成交量
								done_price   ,   --成交价
								eo_flag      ,   --开平标记
								sh_flag      ,   --投保标记
								bs_flag      ,   --买卖方向
								''       ,       --系统号
								0      ,         --成交号
								'' ,             --交易所成交号
								''      ,        --席位号
								currency_code,   --币种
								''    ,          --成交时间
								sum(frzn_commi), 	--手续费
								oper_code,				--操作员
								force_offset	--强平标志 20061123 6.4.0.1
							FROM   cust_real_done
							WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
							AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
							AND	(cust_no = @mi_cust_no)
							AND	oper_code = @mi_oper_code
							AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
							--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
							GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
		          			end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
									select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
				--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
				--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--and （操作员 = 输入操作员），
				--（输入币种 = '' or currency_code = 输入币种）
				--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
	          			--insert into #tmp
	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and （输入客户号 = '' or 客户号 = 输入客户号）
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and （操作员 = 输入操作员）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          		--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
	          			if @if_batch = '1'
					begin
		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			SELECT entrust_no   ,  --委托号
			          			       cust_no      ,  --客户号
			          			       cust_name    ,  --客户名称
			          			       tx_no        ,  --交易编码
			          			       exch_code    ,  --交易所代码
			          			       vari_code    ,  --品种代码
			          			       deliv_date   ,  --交割期
			          			       done_qty	    ,  --成交量
			          			       done_price   ,  --成交价
			          			       eo_flag      ,  --开平标记
			          			       sh_flag      ,  --投保标记
			          			       bs_flag      ,  --买卖方向
			          			       sys_no       ,  --系统号
			          			       done_no      ,  --成交号
			          			       exch_done_no ,  --交易所成交号
			          			       seat_no      ,  --席位号
			          			       currency_code,  --币种
			          			       done_time    ,  --成交时间
			          			       frzn_commi   , 	--手续费
			          			       oper_code,				--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          			SELECT entrust_no   ,  --委托号
			          			       cust_no      ,  --客户号
			          			       cust_name    ,  --客户名称
			          			       tx_no        ,  --交易编码
			          			       exch_code    ,  --交易所代码
			          			       vari_code    ,  --品种代码
			          			       deliv_date   ,  --交割期
			          			       done_qty	    ,  --成交量
			          			       done_price   ,  --成交价
			          			       eo_flag      ,  --开平标记
			          			       sh_flag      ,  --投保标记
			          			       bs_flag      ,  --买卖方向
			          			       sys_no       ,  --系统号
			          			       done_no      ,  --成交号
			          			       exch_done_no ,  --交易所成交号
			          			       seat_no      ,  --席位号
			          			       currency_code,  --币种
			          			       done_time    ,  --成交时间
			          			       frzn_commi   , 	--手续费
			          			       oper_code,				--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				--查询《客户实时成交表》，获得输出信息，查询条件是
				--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
				--and (输入席位号 = '' or 席位号 = 输入席位号)
				--and（客户号 In 《客户基本信息》表中查到的所有输入客户类中的客户号）
				--and （操作员 = 输入操作员）
				--（输入币种 = '' or currency_code = 输入币种）
					--insert into #tmp
					SELECT entrust_no   ,  --委托号
					       cust_no      ,  --客户号
					       cust_name    ,  --客户名称
					       tx_no        ,  --交易编码
					       exch_code    ,  --交易所代码
					       vari_code    ,  --品种代码
					       deliv_date   ,  --交割期
					       done_qty	    ,  --成交量
					       done_price   ,  --成交价
					       eo_flag      ,  --开平标记
					       sh_flag      ,  --投保标记
					       bs_flag      ,  --买卖方向
					       sys_no       ,  --系统号
					       done_no      ,  --成交号
					       exch_done_no ,  --交易所成交号
					       seat_no      ,  --席位号
					       currency_code,  --币种
					       done_time    ,  --成交时间
					       frzn_commi   , 	--手续费
					       oper_code,				--操作员
					       force_offset	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		  			--输出合计记录
		  			if @mi_sum_flag <> '1'
		  			begin
		  				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
					if @if_batch = '1'
					begin
						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

						if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
							SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

						end
						else
						begin
							SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

						end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
					          			FROM   cust_real_done
					          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
					          		end
					          		else
					          		begin
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
	          			FROM   cust_real_done
	          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
	          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
	          			AND	cust_no IN (SELECT cust_no
	          					    FROM   cust_basic
	          					    WHERE  cust_class LIKE @mi_cust_class)
	          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
	          			--zlm 20100421 6.8.2.1
				        and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
	          			if @if_batch = '1'
					begin
		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			and	cust_no in (select cust_no from #tmp_cust)
		          			AND	oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			and	cust_no in (select cust_no from #tmp_cust)
				          			AND	oper_code = @mi_oper_code
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
			          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
						end
						else
						begin
			          			SELECT entrust_no   ,	--委托号
			          			       cust_no      ,   --客户号
			          			       cust_name    ,   --客户名称
			          			       tx_no        ,   --交易编码
			          			       exch_code    ,   --交易所代码
			          			       vari_code    ,   --品种代码
			          			       deliv_date   ,   --交割期
			          			       sum(done_qty),   --成交量
			          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
			          			       eo_flag      ,   --开平标记
			          			       sh_flag      ,   --投保标记
			          			       bs_flag      ,   --买卖方向
			          			       sys_no       ,   --系统号
			          			       0      ,         --成交号
			          			       '' ,             --交易所成交号
			          			       seat_no      ,   --席位号
			          			       currency_code,   --币种
			          			       ''    ,          --成交时间
			          			       sum(frzn_commi), --手续费
			          			       oper_code,	--操作员
			          			       force_offset	--强平标志 20061123 6.4.0.1
			          			FROM   cust_real_done
			          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
			          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
			          			AND	(cust_no = @mi_cust_no)
			          			AND	oper_code = @mi_oper_code
			          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
			          			--zlm 20100421 6.8.2.1
				        		and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
			          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1
			        		end

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if (@mi_cust_no = '')
							begin
				          			if @t_vari_code <> '' and @t_deliv_date <> ''
			          				begin
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
					          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
					          			FROM	cust_real_done
					          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
					          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
					          			AND	(cust_no = @mi_cust_no)
					          			AND	oper_code = @mi_oper_code
					          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
					          			AND	bs_flag = '0'
					          			--zlm 20100421 6.8.2.1
				        				and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

					          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			--6.3.0.1 20061103 把cust_real_done查询条件中的cust_no的or连接拆分成if else结构
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if (@mi_cust_no = '')
		          				begin
		          					if @t_vari_code <> '' and @t_deliv_date <> ''
		          					begin
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          				select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
					          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		ELSE IF @t_if_access = '1'	--有限制
		BEGIN
		--6.
			--select @test = '6'
			IF @mi_done_flag = '1' AND @mi_bind_flag = '1'
			BEGIN
	          		IF @mi_cust_no <> ''
	          		BEGIN

	          			if @if_batch = '1'
					begin
						SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						--判断本操作员是否有带该客户的权限，如果没有，报错，退出
						EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
						IF @ocode <> 0
						BEGIN
							GOTO l_fatal
						END
						--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
						--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
						--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
						--and （客户号 = 输入客户号）
						--and (输入席位号 = '' or 席位号 = 输入席位号)，
						--（输入币种 = '' or currency_code = 输入币种）
						--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
						--insert into #tmp
		          			SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类）），
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			--insert into #tmp
	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，查询条件是
		          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--（输入币种 = '' or currency_code = 输入币种）
		          			--insert into #tmp
		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
		          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
		          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员），
		          		--（输入币种 = '' or currency_code = 输入币种）
		          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
		          			--insert into #tmp
		          			SELECT 0   ,		--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,          --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       done_price   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       ''       ,       --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       ''      ,        --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员），
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			--insert into #tmp
	          			SELECT 0   ,		--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,          --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       done_price   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       ''       ,       --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       ''      ,        --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,done_price,bs_flag,sh_flag,eo_flag,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          		--查询《客户实时成交表》，获得输出信息，查询条件是
		          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员）
		          		--（输入币种 = '' or currency_code = 输入币种）
		          			--insert into #tmp
		          			SELECT entrust_no   ,  --委托号
		          			       cust_no      ,  --客户号
		          			       cust_name    ,  --客户名称
		          			       tx_no        ,  --交易编码
		          			       exch_code    ,  --交易所代码
		          			       vari_code    ,  --品种代码
		          			       deliv_date   ,  --交割期
		          			       done_qty	    ,  --成交量
		          			       done_price   ,  --成交价
		          			       eo_flag      ,  --开平标记
		          			       sh_flag      ,  --投保标记
		          			       bs_flag      ,  --买卖方向
		          			       sys_no       ,  --系统号
		          			       done_no      ,  --成交号
		          			       exch_done_no ,  --交易所成交号
		          			       seat_no      ,  --席位号
		          			       currency_code,  --币种
		          			       done_time    ,  --成交时间
		          			       frzn_commi   , 	--手续费
		          			       oper_code,				--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，查询条件是
	          		--（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员）
	          		--（输入币种 = '' or currency_code = 输入币种）
	          			--insert into #tmp
	          			SELECT entrust_no   ,  --委托号
	          			       cust_no      ,  --客户号
	          			       cust_name    ,  --客户名称
	          			       tx_no        ,  --交易编码
	          			       exch_code    ,  --交易所代码
	          			       vari_code    ,  --品种代码
	          			       deliv_date   ,  --交割期
	          			       done_qty	    ,  --成交量
	          			       done_price   ,  --成交价
	          			       eo_flag      ,  --开平标记
	          			       sh_flag      ,  --投保标记
	          			       bs_flag      ,  --买卖方向
	          			       sys_no       ,  --系统号
	          			       done_no      ,  --成交号
	          			       exch_done_no ,  --交易所成交号
	          			       seat_no      ,  --席位号
	          			       currency_code,  --币种
	          			       done_time    ,  --成交时间
	          			       frzn_commi   , 	--手续费
	          			       oper_code,				--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			END
		          			--insert into #tmp
		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--and    oper_code = @mi_oper_code
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类）），
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
						SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
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
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
		          		--判断本操作员是否有带该客户的权限，如果没有，报错，退出
		          			EXEC verify_oper_cust @mi_oper_code, @mi_cust_no, @ocode output, @omsg output
		          			IF @ocode <> 0
		          			BEGIN
		          				GOTO l_fatal
		          			end
		          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
		          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
		          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
		          		--and （客户号 = 输入客户号）
		          		--and (输入席位号 = '' or 席位号 = 输入席位号)
		          		--and （操作员 = 输入操作员），
		          		--（输入币种 = '' or currency_code = 输入币种）
		          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种
		          			--insert into #tmp
		          			SELECT entrust_no   ,	--委托号
		          			       cust_no      ,   --客户号
		          			       cust_name    ,   --客户名称
		          			       tx_no        ,   --交易编码
		          			       exch_code    ,   --交易所代码
		          			       vari_code    ,   --品种代码
		          			       deliv_date   ,   --交割期
		          			       sum(done_qty),   --成交量
		          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
		          			       eo_flag      ,   --开平标记
		          			       sh_flag      ,   --投保标记
		          			       bs_flag      ,   --买卖方向
		          			       sys_no       ,   --系统号
		          			       0      ,         --成交号
		          			       '' ,             --交易所成交号
		          			       seat_no      ,   --席位号
		          			       currency_code,   --币种
		          			       ''    ,          --成交时间
		          			       sum(frzn_commi), --手续费
		          			       oper_code,	--操作员
		          			       force_offset	--强平标志 20061123 6.4.0.1
		          			FROM   cust_real_done
		          			WHERE  (@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
		          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
		          			AND	cust_no = @mi_cust_no
		          			AND     oper_code = @mi_oper_code
		          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
		          			--zlm 20100421 6.8.2.1
				        	and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))
		          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

		          			select @rowcount_var = @@rowcount

		          			if @mi_subtotal = '1'
			          		begin
			          			if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
			          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
				          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
				          			FROM	cust_real_done
				          			WHERE	(@mi_contract_code = '' or ((@t_vari_code = '' or vari_code = (@t_vari_code)) and (@t_deliv_date = '' or deliv_date like (@t_deliv_date+'%'))))
				          			AND	(@mi_seat_no = '' OR seat_no = @mi_seat_no)
				          			AND	cust_no = @mi_cust_no
				          			AND	(@mi_currency_code = '' OR currency_code = @mi_currency_code)
				          			and	oper_code = @mi_oper_code
				          			AND	bs_flag = '0'
				          			--zlm 20100421 6.8.2.1
				        			and    (@mi_eo_flag = '' or eo_flag  in (@a,@b))

				          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
		          			--输出合计记录
		          			if @mi_sum_flag <> '1'
		          			begin
		          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          				begin
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
				          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
	          		--查询《客户实时成交表》，获得输出信息，输出中的非group by中包含的字段
	          		--或者通过它们能够唯一确定的字段外都置为空或者0，其中的成交数量为sum(成交数量) as 成交数量，
	          		--查询条件是（（输入合约号 = ''）or （品种代码 = 拆分的品种代码 and 交割期 = 拆分的交割期））
	          		--and (输入席位号 = '' or 席位号 = 输入席位号)
	          		--and（客户号 in （《操作员所带所有客户》表中查到的该操作员可带的客户号，查询条件输入客户类 = '' or 客户类 = 输入客户类））
	          		--and （操作员 = 输入操作员），
	          		--（输入币种 = '' or currency_code = 输入币种）
	          		--group by 客户号，交易编码，品种代码，交割期，成交价格，买卖标记，投保标记，开平标记，币种。
	          			--insert into #tmp
	          			SELECT entrust_no   ,	--委托号
	          			       cust_no      ,   --客户号
	          			       cust_name    ,   --客户名称
	          			       tx_no        ,   --交易编码
	          			       exch_code    ,   --交易所代码
	          			       vari_code    ,   --品种代码
	          			       deliv_date   ,   --交割期
	          			       sum(done_qty),   --成交量
	          			       round(sum(done_qty*done_price)/sum(done_qty),2)   ,   --成交价
	          			       eo_flag      ,   --开平标记
	          			       sh_flag      ,   --投保标记
	          			       bs_flag      ,   --买卖方向
	          			       sys_no       ,   --系统号
	          			       0      ,         --成交号
	          			       '' ,             --交易所成交号
	          			       seat_no      ,   --席位号
	          			       currency_code,   --币种
	          			       ''    ,          --成交时间
	          			       sum(frzn_commi), --手续费
	          			       oper_code,	--操作员
	          			       force_offset	--强平标志 20061123 6.4.0.1
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
	          			GROUP BY entrust_no,cust_no,cust_name,tx_no,exch_code,vari_code,deliv_date,bs_flag,sh_flag,eo_flag,sys_no,seat_no,currency_code,oper_code,force_offset	--强平标志 20061123 6.4.0.1

	          			select @rowcount_var = @@rowcount

	          			if @mi_subtotal = '1'
		          		begin
		          			if @t_vari_code <> '' and @t_deliv_date <> ''
	          				begin
		          				select	'', '(买小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''
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
			          			select	'', '(买小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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

			          			select	'', '(卖小计)','' , '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''
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
	          			--输出合计记录
	          			if @mi_sum_flag <> '1'
	          			begin
	          				if @t_vari_code <> '' and @t_deliv_date <> ''
		          			begin
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), sum(done_price * done_qty)/sum(done_qty), '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			          			select '', '(合计)'+convert(varchar,count(*))+'条','', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi),'',''	--强平标志 20061123 6.4.0.1
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
			select @ocode = -2, @omsg = '操作员号不存在或操作员访问限制无效'
			goto l_fatal
		end

	          select @ocode = @@error
	          if @ocode <> 0
	          begin
	          	select @ocode = -3, @omsg = '查询客户当日成交表失败'
	          	goto l_fatal
	          end
	end

	  --输出结果集和合计记录
	  --select * from #tmp
	  --select '', '合计', '', '','','','', sum(done_qty), '', '','','','','','','','','', sum(frzn_commi) from #tmp

          return 0
l_fatal:
          select "fatal"=@ocode, @omsg
          return -1
end
go
declare @update_flag char
exec	sp_upgrade_control
	'6.8.2.1',			--版本号
	'2',				--操作标志
	'p854042',			--sp功能号
	@update_flag output		--修改标志
if @update_flag <> '0'
	print '出现错误。创建存储过程: 854042 , 查询当日成交,失败！'
else
	print '创建存储过程: 854042 , 查询当日成交'
go
