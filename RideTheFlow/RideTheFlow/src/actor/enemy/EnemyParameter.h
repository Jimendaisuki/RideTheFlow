#pragma once

/****�U���͊֌W****/
//��̍U����
const float ArrowPower = 1.0f;
//��C�̍U����
const float CannonPower = 5.0f;
//�o���X�^�̍U����
const float VaristorPower = 2.0f;
//�������̍U����
const float DoragonSperarPower = 10.0f;


/****�G�̍U���̑傫��****/
//��̑傫��
const float ArrowSize = 4.0f;
//�C�e�̑傫��
const float ConnonBulletSize = 10.0f;
//�o���X�^�e�̑傫��
const float VaristorBulletSize = 6.0f;

/***�G�̍U���̃X�s�[�h***/
//��̃X�s�[�h
const float ArrowSpeed = 5.0f;
//�C�e�̃X�s�[�h
const float CannonSpeed = 5.0f;
//�o���X�^�̃X�s�[�h
const float VaristorSpeed = 5.0f;

/***����***/
//�ǂ̂��炢�J�����̑O�̏ꏊ�ɒʏ�U�����邩(�_�b�V�����͖���)
const float cameraFrontAttack = 10.0f;

/****�G�R��****/
//�R���̃X�s�[�h
const float ArmySpeed = 50.0f;
//�R���̍U���N�[���^�C��
const float ArmyAttackTime = 5.0f;
//�R���̍U���͈�
const float ArmyRange = 3000.0f;
//�R�����v���C���[���猩�Ăǂ��܂ŋ߂Â���(�x��)�@�@��:0�x�ɂ����ꍇ�v���C���[�̐^���ɂ܂ňړ�����
const float ArmyNear = 45.0f;
//�R�������ɔ��˂����̖{��
const int ArmyArrorwNum = 10;

//�R������v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookArmyAttackTime = 20.0f;
//�R������v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookArmyArrorwNum = 0;

//�R���̍U�����x
const float ArmyArrowAccuracy = 100.0f;
//�R���̍U��������̉e�����󂯂銄��
const float ArmyWindPercentage = 100.0f;


/****�G�o���X�^****/

//�o���X�^�̍U���N�[���^�C��
const float VaristorAttackTime = 5.0f;
//�o���X�^�����ɔ��˂����̐�
const int VaristorArrorwNum = 2;
//�o���X�^�̍U���͈�
const float VaristorRange = 1000.0f;
//�o���X�^�����˂ł���Z�����ɂ����ō��p�x�i�x�j
const float VaristorAttackMaxAngle = 90.0f;
//�o���X�^�����˂ł���Z�����ɂ����ŏ��p�x�i�x�j
const float VaristorAttackMinAngle = -90.0f;
//�o���X�^�̏����x
const float VaristorInitialVelocity = 100.0f;
//�o���X�^�̐��񑬓x
const float VaristorSwingSpeed = 100.0f;

//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookVaristorAttackTime = 10.0f;
//�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float NotLookVaristorArrowNum = 0;

//�o���X�^�U�����x(�������قǍ����x)
const float VaristorArrowAccuracy = 10.0f;
//�o���X�^�̍U��������̉e�����󂯂銄��
const float VaristorWindPercentage = 75.0f;



/****�G��C****/

//��C�̍U���N�[���^�C��
const float CannonAttackTime = 0.1f;
//��C�̍U���͈�
const float CannonRange = 1000.0f;
//��C�����ɔ��˂���C�e�̐�
const int CannonShellNum = 1;
//��C�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  CannonAttackMaxAngle = 90.0f;
//��C�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float CannonAttackMinAngle = -90.0f;
//��C�̋ʂ̏����x
const float CannonInitialVelocity = 200.0f;
//��C�̐��񑬓x
const float ConnonSwingSpeed = 100.0f;

//��C����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float NotLookCannonAttackTime = 30.0f;
//��C����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float NotLookCannonShellNum = 0;

//��C�U�����x(�������قǍ����x)
const float CannonShellAccuracy = 10.0f;
//��C�̍U��������̉e�����󂯂銄��
const float CannonWindPercentage = 50.0f;


/****�G�̑D****/

//�D��HP
const float ShipHp = 10.0f;
//�D���g���l�[�h�Ŏ󂯂�_���[�W
const float ShipDamegeTornado = 10.0f;
//�D������Ŏ󂯂�_���[�W
const float ShipDamegeWind = 5.0f;
//�D����C�C�Ŏ󂯂�_���[�W
const float ShipDamegeWindBall = 5.0f;

//�D�̖��G����
const float ShipInvincibleTime = 3.0f;


//�D�̃X�s�[�h
const float ShipSpeed = 50.0f;
//�D�̍�����ς���X�s�[�h
const float ShipUpDownSpeed = 50.0f;
//�D�̐��񑬓x
const float ShipSwingSpeed = 50.0f;
//�D�o���X�^�̍U���N�[���^�C��
const float ShipVaristorAttackTime = 2.0f;
//�D�o���X�^�����ɔ��˂����̐�
const int ShipVaristorArrorwNum = 2;
//�D�o���X�^�̍U���͈�
const float ShipVaristorRange = 1000.0f;
//�D�o���X�^�����˂ł���Z�����ɂ����ō��p�x�i�x�j
const float ShipVaristorAttackMaxAngle = 90.0f;
//�D�o���X�^�����˂ł���Z�����ɂ����ŏ��p�x�i�x�j
const float ShipVaristorAttackMinAngle = -90.0f;
//�D�o���X�^�̏����x
const float ShipVaristorInitialVelocity = 200.0f;
//�D�o���X�^�̐��񑬓x
const float ShipVaristorSwingSpeed = 100.0f;

//�D�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float ShipNotLookVaristorAttackTime = 10.0f;
//�D�o���X�^����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂����̖{��
const float ShipNotLookVaristorArrowNum = 0;


//�D��C�̍U���N�[���^�C��
const float ShipCannonAttackTime = 2.0f;
//�D��C�̍U���͈�
const float ShipCannonRange = 1000.0f;
//�D��C�����ɔ��˂���C�e�̐�
const int ShipCannonShellNum = 2;
//�D��C�̔��˂ł���Z�����ɂ����ō��p�x�i�x�j
const float  ShipCannonAttackMaxAngle = 90.0f;
//�D��C�̔��˂ł���Z�����ɂ����Œ�p�x�i�x�j
const float ShipCannonAttackMinAngle = -90.0f;
//�D��C�̋ʂ̏����x
const float ShipCannonInitialVelocity = 200.0f;
//�D��C�̐��񑬓x
const float ShipConnonSwingSpeed = 100.0f;

//�D��C����v���C���[�������Ă��Ȃ��Ƃ��̍U���N�[���^�C��
const float ShipNotLookCannonAttackTime = 30.0f;
//�D��C����v���C���[�������Ă��Ȃ��Ƃ��̈��ɔ��˂���C�e�̐�
const float ShipNotLookCannonShellNum = 0;


/***������***/

//�������̃N�[���^�C��
const float DoragonSpearAttackTime = 5.0f;
//�v���C���[�������������ɓ�����������U�����鎞�܂ł̎���
const float DoragonSpearWithinTime = 1.0f;
//���������ő�ɐL�т�܂ł̎���
const float DoragonSpearMaxTime = 10.0f;
//�����������S�ɏo�Ă����ɂƂǂ܂鎞��
const float DoragonSpearStopTime = 1.0f;
