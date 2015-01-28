//
//  GPDInStoreViewController.m
//  GPShopper-iOS
//
//  Created by Patrick Caraher on 1/7/15.
//  Copyright (c) 2015 James Lee. All rights reserved.
//

#import "GPDInStoreViewController.h"

#define kRequestAssociateTitle @"Request Associate"
#define kStoreMapTitle @"Store Map"
#define kStoreInformationTitle @"Store Information"
#define kBeaconRefreshTitle @"Beacon Refresh"

#define kInStoreTableViewCellIdentifier @"InStoreCell"

@interface GPDInStoreViewController () <UITableViewDataSource,UITableViewDelegate>

@property (nonatomic, strong) NSArray *rows;
@property (nonatomic, strong) NSDictionary *viewControllerForRow;

@end

@implementation GPDInStoreViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    self.rows = @[kRequestAssociateTitle, kStoreMapTitle, kStoreInformationTitle,kBeaconRefreshTitle];
    self.viewControllerForRow = @{kRequestAssociateTitle : @"GPDRequestAssociateViewController"};

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.rows.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:kInStoreTableViewCellIdentifier];
    NSString *title = [self.rows objectAtIndex:indexPath.row];
    
    if (cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kInStoreTableViewCellIdentifier];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    cell.textLabel.text = title;
    
    return cell;
}

#pragma mark UITableViewDelegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *rowName = self.rows[indexPath.row];
    NSString *vcName = [self.viewControllerForRow valueForKey:[self.rows objectAtIndex:indexPath.row]];
    
    if (vcName)
    {
        Class myClass = NSClassFromString(vcName);
        UIViewController *vc = [[myClass alloc] initWithNibName:vcName bundle:[NSBundle mainBundle]];
        [self.navigationController pushViewController:vc animated:YES];
    }
    else if ([kBeaconRefreshTitle compare:rowName] == NSOrderedSame)
    {
        [[SCBeaconDeviceManager defaultDataCoordinator] clearNotificationHistory];
        [CustomAlertView showSimpleAlertWithTitle:@"Beacons Cleared" message:@"Your Beacon history has been cleared."];
    }
}


@end
