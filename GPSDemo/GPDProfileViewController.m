//
//  GPDProfileViewController.m
//  GPShopper-iOS
//
//  Created by Matthew Reed on 10/28/14.
//  Copyright (c) 2014 James Lee. All rights reserved.
//

#import "GPDProfileViewController.h"
#import "GPDLoginViewController.h"

@interface GPDProfileViewController ()

@property (strong, nonatomic) IBOutlet UILabel *firstNameLabel;
@property (strong, nonatomic) IBOutlet UILabel *lastNameLabel;
@property (strong, nonatomic) IBOutlet UILabel *emailLabel;
@property (strong, nonatomic) IBOutlet UIButton *loginLogoutButton;

@property (strong, nonatomic) SCProfile *profile;
@property (strong, nonatomic) SCSession *session;
@end

@implementation GPDProfileViewController

@synthesize firstNameLabel;
@synthesize lastNameLabel;
@synthesize emailLabel;
@synthesize loginLogoutButton;
@synthesize profile;
@synthesize session;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        NSString *requestURL = [NSString stringWithFormat:@"https://%@/mobile", [NSBundle standardClientHostName]];
        [SCSession setRequestUrl:requestURL];
        [SCProfile setRequestUrl:requestURL];
        
        profile = [SCProfile defaultProfile];
        session = [SCSession defaultSession];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [profile fetch];
    [profile addObserver:self forKeyPath:@"fetchStatus" options:0 context:nil];
    [profile addObserver:self forKeyPath:@"updateStatus" options:0 context:nil];
    [[NSNotificationCenter defaultCenter] addObserverForName:@"scsession_updated" object:session queue:nil usingBlock:^(NSNotification *note) {
        if (!session.exists) {
            [loginLogoutButton setTitle:@"Login" forState:UIControlStateNormal];
            [profile clear];
            firstNameLabel.hidden = YES;
            lastNameLabel.hidden = YES;
            emailLabel.hidden = YES;
            firstNameLabel.text = nil;
            lastNameLabel.text = nil;
            emailLabel.text = nil;
        } else {
            [loginLogoutButton setTitle:@"Logout" forState:UIControlStateNormal];
        }
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)loginLogoutButtonPressed:(id)sender {
    if (session.exists) {
        [session destroy];
    } else {
        [self showLogin];
    }
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"fetchStatus"]) {
        switch (profile.fetchStatus) {
            case SCProfileRemoteBusy:
                
                break;
            case SCProfileRemoteFail:
                [self showLogin];
                break;
            case SCProfileRemoteNone:
                
                break;
            case SCProfileRemoteSuccess:
                [self performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
                break;
        }
    } else if ([keyPath isEqualToString:@"updateStatus"]) {
            switch (profile.fetchStatus) {
                case SCProfileRemoteBusy:
                    
                    break;
                case SCProfileRemoteFail:
                    [self showLogin];
                    break;
                case SCProfileRemoteNone:
                    
                    break;
                case SCProfileRemoteSuccess:
                    [self performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
                    break;
            }
    }
}

- (void)showLogin {
    GPDLoginViewController *vc = [[GPDLoginViewController alloc] initWithNibName:@"GPDLoginViewController" bundle:nil];
    vc.title = @"Login";
    UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:vc];
    [self presentViewController:nc animated:YES completion:nil];
}

- (void)reloadData {
    firstNameLabel.hidden = NO;
    lastNameLabel.hidden = NO;
    emailLabel.hidden = NO;
    firstNameLabel.text = profile.firstName;
    lastNameLabel.text = profile.lastName;
    emailLabel.text = profile.email;
    //[loginLogoutButton setTitle:@"Logout" forState:UIControlStateNormal];
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
