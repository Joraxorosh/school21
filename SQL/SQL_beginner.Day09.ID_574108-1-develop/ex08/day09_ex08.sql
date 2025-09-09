create or replace function fnc_fibonacci(pstop INTEGER DEFAULT 10)
	returns table(
                current BIGINT)
    language sql
as
$BODY$
with recursive f(current, next) as
	(select 0::BIGINT, 1::BIGINT
     union all
     select f.next, f.current + f.next
     from f
     where f.next < fnc_fibonacci.pstop)
select current
from f;
$BODY$;



select * from fnc_fibonacci(100);
--select * from fnc_fibonacci();