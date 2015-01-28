//
//  GPDRequestAssociateViewController.m
//  GPShopper-iOS
//
//  Created by Patrick Caraher on 1/7/15.
//  Copyright (c) 2015 James Lee. All rights reserved.
//

#import "GPDRequestAssociateViewController.h"
#import <GPShopper/GPShopper.h>

#define kNeedAssistanceTag 0
#define kCheckoutTag 1

@interface GPDRequestAssociateViewController ()
@property (strong, nonatomic) IBOutlet UISwitch *needAssistanceSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *checkoutSwitch;
@end

@implementation GPDRequestAssociateViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self.needAssistanceSwitch setOn:[[SCBeaconDeviceManager defaultDataCoordinator] isRequestingSalesAssociate]];
    [self.checkoutSwitch setOn:[[SCBeaconDeviceManager defaultDataCoordinator] isRequestingSalesAssociate2]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)clickedSwitch:(id)sender
{
    SCBeaconDeviceManager *manager = [SCBeaconDeviceManager defaultDataCoordinator];

    switch ([sender tag])
    {
        case kNeedAssistanceTag:
            ([sender isOn]) ? [manager requestSalesAssociate] : [manager clearRequestSalesAssociate];
            break;
        case kCheckoutTag:
            ([sender isOn]) ? [manager requestSalesAssociate2] : [manager clearRequestSalesAssociate2];
            break;
        default:
            break;
    }
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
