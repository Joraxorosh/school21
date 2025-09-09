-- session #1
begin transaction isolation level repeatable read;
select sum(rating) from pizzeria;
select sum(rating) from pizzeria;
commit;
select sum(rating) from pizzeria;

-- session #2
begin transaction isolation level repeatable read;
insert into pizzeria (id, name, rating) values (11, 'Kazan Pizza 2', 4);
commit;
select sum(rating) from pizzeria;