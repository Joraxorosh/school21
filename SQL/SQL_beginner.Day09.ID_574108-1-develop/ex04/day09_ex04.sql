create or replace function fnc_persons_female()
returns table(id BIGINT, name VARCHAR, age INTEGER, gender VARCHAR, address VARCHAR) as $$
select id, name, age, gender, address
from person
where gender = 'female';
$$ language sql;

create or replace function fnc_persons_male()
returns table(id BIGINT, name VARCHAR, age INTEGER, gender VARCHAR, address VARCHAR) as $$
select id, name, age, gender, address
from person
where gender = 'male';
$$ language sql;

select * from fnc_persons_male();
--select * from fnc_persons_female();