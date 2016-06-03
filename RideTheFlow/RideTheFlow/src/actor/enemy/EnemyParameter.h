#pragma once

/***����***/
//�ǂ̂��炢�J�����̑O�̏ꏊ�ɒʏ�U�����邩(�_�b�V�����͖���)
const float cameraFrontAttack = 10.0f;


/****�G�R��****/

//�R���̃X�s�[�h
const float ArmySpeed = 50.0f;
//�R���̍U���N�[���^�C��
const float ArmyAttackTime = 0.5f;
//�R���̍U���͈�
const float ArmyRange = 200.0f;
//�R�����v���C���[���猩�Ăǂ��܂ŋ߂Â���(�x��)�@�@��:0�x�ɂ����ꍇ�v���C���[�̐^���ɂ܂ŗ���
const float ArmyNear = 45.0f;
//�R�������ɔ��˂����̖{��
const int ArmyArrorwNum = 10;

//�R������v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookArmyAttackTime = 20.0f;
//�R������v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookArmyArrorwNum = 5;

//�R���̍U�����x
const float ArmyArrowAccuracy = 50.0f;
//�R���̍U��������̉e�����󂯂銄��
const float ArmyWindPercentage = 80.0f;


/****�G�o���X�^****/

//�o���X�^�̒e�X�s�[�h
const float VaristorSpeed = 3.0f;
//�o���X�^�̍U���N�[���^�C��
const float VaristorAttackTime = 5.0f;
//�o���X�^�����ɔ��˂����̐�
const int VaristorArrorwNum = 2;
//�o���X�^�̍U���͈�
const float VaristorRange = 300.0f;
//�o���X�^�����˂ł���Z�����ɂ����ō��p�x�i�x�j
const float VaristorAttackMaxAngle = 45.0f;
//�o���X�^�����˂ł���Z�����ɂ����ŏ��p�x�i�x�j
const float VaristorAttackMinAngle = -45.0f;
//�o���X�^�̏����x
const float VaristorInitialVelocity = 60.0f;
//�o���X�^�̐��񑬓x
const float VaristorSwingSpeed = 50.0f;

//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookVaristorAttackTime = 10.0f;
//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookVaristorArrowNum = 2;

//�o���X�^�U�����x(�������قǍ����x)
const float VaristorArrowAccuracy = 10.0f;
//�o���X�^�̍U��������̉e�����󂯂銄��
const float VaristorWindPercentage = 100.0f;



/****�G��C****/

//��C�̒e�X�s�[�h
const float CannonSpeed = 3.0f;
//��C�̍U���N�[���^�C��
const float CannonAttackTime = 10.0f;
//��C�̍U���͈�
const float CannonRange = 300.0f;
//��C�����ɔ��˂���C�e�̐�
const int CannonShellNum = 1;
//��C�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  CannonAttackMaxAngle = 45.0f;
//��C�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float CannonAttackMinAngle = -45.0f;
//��C�̋ʂ̏����x
const float CannonInitialVelocity = 100.0f;
//��C�̐��񑬓x
const float ConnonSwingSpeed = 50.0f;

//��C����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookCannonAttackTime = 30.0f;
//��C����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float NotLookCannonShellNum = 1;

//��C�U�����x(�������قǍ����x)
const float CannonShellAccuracy = 10.0f;
//��C�̍U��������̉e�����󂯂銄��
const float CannonWindPercentage = 100.0f;


/****�G�̑D****/

//�D�̃X�s�[�h
const float ShipSpeed = 3.0f;
//�D�̍U���N�[���^�C��
const float ShipAttackTime = 10.0f;
//�D�̍U���͈�
const float ShipRange = 300.0f;
//�D�����ɔ��˂���C�e�̐�
const int ShipShellNum = 1;
//�D�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  ShipAttackMaxAngle = 45.0f;
//�D�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float ShipAttackMinAngle = -45.0f;
//�D�̋ʂ̏����x
const float ShipInitialVelocity = 100.0f;
//�D�̐��񑬓x
const float ShipSwingSpeed = 50.0f;

//�D����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookShipAttackTime = 30.0f;
//�D����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float NotLookShipShellNum = 1;

//�D�U�����x(�������قǍ����x)
const float ShipAttackAccuracy = 10.0f;
//�D�̍U��������̉e�����󂯂銄��
const float ShipWindPercentage = 100.0f;
