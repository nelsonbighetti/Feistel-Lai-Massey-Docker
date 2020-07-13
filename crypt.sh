mkdir ./workdir/input
mkdir ./workdir/key
mkdir ./workdir/output

f_input="$(basename -- $2)"
f_key="$(basename -- $3)"
f_output="$(basename -- $4)"

cp $2 ./workdir/input/$f_input
cp $3 ./workdir/key/$f_key

docker exec flm_crypto sh flm_run.sh $1 $f_input $f_key $f_output

cp ./workdir/output/$f_output $4
rm -rf ./workdir/*