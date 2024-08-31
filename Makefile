.PHONY: git-submodule, qmk-clean, qmk-init, qmk-compile, qmk-flash, qmk-init-all, qmk-compile-all, vial-qmk-clean, vial-qmk-init, vial-qmk-compile, vial-qmk-flash, vial-qmk-init-all, vial-qmk-compile-all, update-all

KB := crkbd 
KM := default

git-submodule:
	git submodule update --remote
	git submodule update --init --recursive

qmk-clean:
	rm -rf src/qmk/qmk_firmware/keyboards/tmp
	cd src/qmk/qmk_firmware; qmk clean

qmk-init:
	$(eval KB := ${kb})
	rm -f src/qmk/qmk_firmware/keyboards/tmp/${KB}
	mkdir -p src/qmk/qmk_firmware/keyboards/tmp
	ln -s $(shell pwd)/keyboards/${KB}/qmk/qmk_firmware src/qmk/qmk_firmware/keyboards/tmp/${KB}
	mkdir -p keyboards/${KB}/qmk/qmk_firmware/.build

qmk-compile:
	$(eval KB := ${kb})
	$(eval KM := ${km})
	$(eval FILE := $(shell echo "${kb}_${km}" | sed 's/\//_/'))
	cd src/qmk/qmk_firmware; qmk compile -kb tmp/${KB} -km ${KM}
	cp src/qmk/qmk_firmware/.build/tmp_${FILE}.hex keyboards/${KB}/qmk/qmk_firmware/.build/${FILE}.hex | true
	cp src/qmk/qmk_firmware/.build/tmp_${FILE}.uf2 keyboards/${KB}/qmk/qmk_firmware/.build/${FILE}.uf2 | true

qmk-flash:
	$(eval KB := ${kb})
	$(eval KM := ${km})
	cd src/qmk/qmk_firmware; qmk flash -kb tmp/${KB} -km ${KM}

qmk-init-all:
	kb=crkbd make qmk-init

qmk-compile-all:
	kb=crkbd km=default make qmk-compile

update-all:
	make git-submodule
	make qmk-clean
	make qmk-init-all
	make qmk-compile-all
