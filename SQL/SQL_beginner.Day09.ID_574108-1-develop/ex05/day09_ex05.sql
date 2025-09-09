drop function if exists fnc_persons_female;
drop function if exists fnc_persons_male;

create or replace function fnc_persons(pgender VARCHAR DEFAULT 'female')
returns table(id BIGINT, name VARCHAR, age INTEGER, gender VARCHAR, address VARCHAR) as $$
select id, name, age, gender, address
from person
where gender = pgender;
$$ language sql;

--select * from fnc_persons(pgender := 'male');
select * from fnc_persons();